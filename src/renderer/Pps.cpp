// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include "anki/renderer/Pps.h"
#include "anki/renderer/Renderer.h"
#include "anki/renderer/Bloom.h"
#include "anki/renderer/Sslf.h"
#include "anki/renderer/Ssao.h"
#include "anki/renderer/Sslr.h"
#include "anki/renderer/Tm.h"
#include "anki/renderer/Is.h"
#include "anki/renderer/Dbg.h"
#include "anki/util/Logger.h"
#include "anki/misc/ConfigSet.h"

namespace anki {

//==============================================================================
Pps::Pps(Renderer* r)
	: RenderingPass(r)
{}

//==============================================================================
Pps::~Pps()
{}

//==============================================================================
Error Pps::initInternal(const ConfigSet& config)
{
	m_enabled = config.get("pps.enabled");
	if(!m_enabled)
	{
		return ErrorCode::NONE;
	}

	ANKI_ASSERT("Initializing PPS");

	m_ssao.reset(getAllocator().newInstance<Ssao>(m_r));
	ANKI_CHECK(m_ssao->init(config));

	m_sslr.reset(getAllocator().newInstance<Sslr>(m_r));
	ANKI_CHECK(m_sslr->init(config));

	m_tm.reset(getAllocator().newInstance<Tm>(m_r));
	ANKI_CHECK(m_tm->create(config));

	m_bloom.reset(getAllocator().newInstance<Bloom>(m_r));
	ANKI_CHECK(m_bloom->init(config));

	m_sslf.reset(getAllocator().newInstance<Sslf>(m_r));
	ANKI_CHECK(m_sslf->init(config));

	// FBO
	m_r->createRenderTarget(
		m_r->getWidth(), m_r->getHeight(),
		PixelFormat(ComponentFormat::R8G8B8, TransformFormat::UNORM),
		1, SamplingFilter::LINEAR, 1, m_rt);

	FramebufferPtr::Initializer fbInit;
	fbInit.m_colorAttachmentsCount = 1;
	fbInit.m_colorAttachments[0].m_texture = m_rt;
	fbInit.m_colorAttachments[0].m_loadOperation =
		AttachmentLoadOperation::DONT_CARE;
	m_fb.create(&getGrManager(), fbInit);

	// SProg
	StringAuto pps(getAllocator());

	pps.sprintf(
		"#define SSAO_ENABLED %u\n"
		"#define BLOOM_ENABLED %u\n"
		"#define SSLF_ENABLED %u\n"
		"#define SHARPEN_ENABLED %u\n"
		"#define GAMMA_CORRECTION_ENABLED %u\n"
		"#define FBO_WIDTH %u\n"
		"#define FBO_HEIGHT %u\n",
		m_ssao->getEnabled(),
		m_bloom->getEnabled(),
		m_sslf->getEnabled(),
		U(config.get("pps.sharpen")),
		U(config.get("pps.gammaCorrection")),
		m_r->getWidth(),
		m_r->getHeight());

	ANKI_CHECK(m_frag.loadToCache(&getResourceManager(),
		"shaders/Pps.frag.glsl", pps.toCString(), "r_"));

	ANKI_CHECK(m_r->createDrawQuadPipeline(m_frag->getGrShader(), m_ppline));

	// LUT
	ANKI_CHECK(loadColorGradingTexture("engine_data/default_lut.ankitex"));

	return ErrorCode::NONE;
}

//==============================================================================
Error Pps::init(const ConfigSet& config)
{
	Error err = initInternal(config);
	if(err)
	{
		ANKI_LOGE("Failed to init PPS");
	}

	return err;
}
//==============================================================================
Error Pps::loadColorGradingTexture(CString filename)
{
	ANKI_CHECK(m_lut.load(filename, &getResourceManager()));
	return ErrorCode::NONE;
}

//==============================================================================
void Pps::run(CommandBufferPtr& cmdb)
{
	ANKI_ASSERT(m_enabled);

	// First SSAO because it depends on MS where HDR depends on IS
	if(m_ssao->getEnabled())
	{
		m_ssao->run(cmdb);
	}

	// Then SSLR because HDR depends on it
	if(m_sslr->getEnabled())
	{
		m_sslr->run(cmdb);
	}

	m_r->getIs().generateMipmaps(cmdb);
	m_tm->run(cmdb);

	if(m_bloom->getEnabled())
	{
		m_bloom->run(cmdb);
	}

	if(m_sslf->getEnabled())
	{
		m_sslf->run(cmdb);
	}

	FramebufferPtr fb = m_fb;
	U32 width = m_r->getWidth();
	U32 height = m_r->getHeight();

	Bool isLastStage = !m_r->getDbg().getEnabled();
	if(isLastStage)
	{
		m_r->getOutputFramebuffer(fb, width, height);
	}

	fb.bind(cmdb);
	cmdb.setViewport(0, 0, width, height);

	m_ppline.bind(cmdb);

	m_r->getIs()._getRt().bind(cmdb, 0);

	if(m_ssao->getEnabled())
	{
		m_ssao->getRt().bind(cmdb, 1);
	}

	if(m_bloom->getEnabled())
	{
		m_bloom->getRt().bind(cmdb, 2);
	}

	if(m_sslf->getEnabled())
	{
		m_sslf->getRt().bind(cmdb, 4);
	}

	m_lut->getGlTexture().bind(cmdb, 3);

	m_tm->getAverageLuminanceBuffer().bindShaderBuffer(cmdb, 0);

	m_r->drawQuad(cmdb);
}

} // end namespace anki
