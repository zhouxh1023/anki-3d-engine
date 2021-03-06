// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include "anki/renderer/MainRenderer.h"
#include "anki/renderer/Renderer.h"
#include "anki/renderer/Is.h"
#include "anki/renderer/Pps.h"
#include "anki/renderer/Dbg.h"
#include "anki/scene/SceneGraph.h"
#include "anki/scene/Camera.h"
#include "anki/util/Logger.h"
#include "anki/renderer/Deformer.h"
#include "anki/util/File.h"
#include "anki/util/Filesystem.h"
#include "anki/core/Counters.h"
#include "anki/core/App.h"
#include "anki/misc/ConfigSet.h"

namespace anki {

//==============================================================================
MainRenderer::MainRenderer()
{}

//==============================================================================
MainRenderer::~MainRenderer()
{
	m_materialShaderSource.destroy(m_alloc);
}

//==============================================================================
Error MainRenderer::create(
	Threadpool* threadpool,
	ResourceManager* resources,
	GrManager* gr,
	AllocAlignedCallback allocCb,
	void* allocCbUserData,
	const ConfigSet& config,
	const Timestamp* globalTimestamp)
{
	ANKI_LOGI("Initializing main renderer...");

	m_alloc = HeapAllocator<U8>(allocCb, allocCbUserData);
	m_frameAlloc = StackAllocator<U8>(allocCb, allocCbUserData, 1024 * 1024);

	// Init default FB
	m_width = config.get("width");
	m_height = config.get("height");
	FramebufferPtr::Initializer fbInit;
	m_defaultFb.create(gr, fbInit);

	// Init renderer
	ConfigSet config2 = config;
	m_renderingQuality = config.get("renderingQuality");
	config2.set("width", m_renderingQuality * F32(m_width));
	config2.set("height", m_renderingQuality * F32(m_height));

	m_r.reset(m_alloc.newInstance<Renderer>());
	ANKI_CHECK(m_r->init(threadpool, resources, gr, m_alloc,
		m_frameAlloc, config2, globalTimestamp));

	initGl();

	// Set the default preprocessor string
	m_materialShaderSource.sprintf(
		m_alloc,
		"#define ANKI_RENDERER_WIDTH %u\n"
		"#define ANKI_RENDERER_HEIGHT %u\n",
		m_r->getWidth(), m_r->getHeight());

	// Init other
	ANKI_CHECK(m_blitFrag.load(
		"shaders/Final.frag.glsl", &m_r->getResourceManager()));

	ANKI_CHECK(m_r->createDrawQuadPipeline(
		m_blitFrag->getGrShader(), m_blitPpline));

	ANKI_LOGI("Main renderer initialized. Rendering size %dx%d",
		m_width, m_height);

	return ErrorCode::NONE;
}

//==============================================================================
Error MainRenderer::render(SceneGraph& scene)
{
	ANKI_COUNTER_START_TIMER(MAIN_RENDERER_TIME);

	GrManager& gl = m_r->getGrManager();
	Array<CommandBufferPtr, RENDERER_COMMAND_BUFFERS_COUNT> cmdbs;
	CommandBufferPtr& cmdb = cmdbs[RENDERER_COMMAND_BUFFERS_COUNT - 1];

	for(U i = 0; i < RENDERER_COMMAND_BUFFERS_COUNT; i++)
	{
		cmdbs[i].create(&gl, m_cbInitHints[i]);
	}

	// Find where the m_r should draw
	Bool rDrawToDefault;
	if(m_renderingQuality == 1.0 && !m_r->getDbg().getEnabled())
	{
		rDrawToDefault = true;
	}
	else
	{
		rDrawToDefault = false;
	}

	if(rDrawToDefault)
	{
		m_r->setOutputFramebuffer(m_defaultFb, m_width, m_height);
	}
	else
	{
		m_r->setOutputFramebuffer(FramebufferPtr(), 0, 0);
	}

	// Run renderer
	m_r->getIs().setAmbientColor(scene.getAmbientColor());
	ANKI_CHECK(m_r->render(scene.getActiveCamera(), cmdbs));

	if(!rDrawToDefault)
	{
		m_defaultFb.bind(cmdb);
		cmdb.setViewport(0, 0, m_width, m_height);

		m_blitPpline.bind(cmdb);

		TexturePtr* rt;

		if(m_r->getPps().getEnabled())
		{
			rt = &m_r->getPps().getRt();
		}
		else
		{
			rt = &m_r->getIs()._getRt();
		}

		//rt = &getMs().getRt2();
		//rt = &getPps().getHdr()._getRt();

		rt->bind(cmdb, 0);

		m_r->drawQuad(cmdb);
	}

	// Flush the last command buffer
	cmdb.flush();

	// Set the hints
	for(U i = 0; i < RENDERER_COMMAND_BUFFERS_COUNT; i++)
	{
		m_cbInitHints[i] = cmdbs[i].computeInitHints();
	}

	ANKI_COUNTER_STOP_TIMER_INC(MAIN_RENDERER_TIME);

	return ErrorCode::NONE;
}

//==============================================================================
void MainRenderer::initGl()
{
	CommandBufferPtr cmdb;
	cmdb.create(&m_r->getGrManager());

	cmdb.enableCulling(true);
	cmdb.setCullFace(GL_BACK);
	cmdb.enablePointSize(true);
	cmdb.flush();
}

//==============================================================================
Dbg& MainRenderer::getDbg()
{
	return m_r->getDbg();
}

//==============================================================================
F32 MainRenderer::getAspectRatio() const
{
	return m_r->getAspectRatio();
}

//==============================================================================
void MainRenderer::prepareForVisibilityTests(Camera& cam)
{
	m_r->prepareForVisibilityTests(cam);
}

} // end namespace anki
