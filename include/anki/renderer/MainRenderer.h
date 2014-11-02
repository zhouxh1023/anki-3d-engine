// Copyright (C) 2014, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_RENDERER_MAIN_RENDERER_H
#define ANKI_RENDERER_MAIN_RENDERER_H

#include "anki/renderer/Renderer.h"

namespace anki {

/// @addtogroup renderer
/// @{

/// Main onscreen renderer
class MainRenderer: public Renderer
{
public:
	MainRenderer();

	~MainRenderer();

	ANKI_USE_RESULT Error init(
		Threadpool* threadpool, 
		ResourceManager* resources,
		GlDevice* gl,
		HeapAllocator<U8>& alloc,
		const ConfigSet& config);

	ANKI_USE_RESULT Error render(SceneGraph& scene);

	/// Save the color buffer to a tga (lossless & uncompressed & slow)
	/// or jpeg (lossy & compressed fast)
	/// @param filename The file to save
	void takeScreenshot(const char* filename);

private:
	ProgramResourcePointer m_blitFrag;
	GlProgramPipelineHandle m_blitPpline;

	/// Optimize job chain
	Array<GlCommandBufferInitHints, JOB_CHAINS_COUNT> m_jobsInitHints; 

	void takeScreenshotTga(const char* filename);
	ANKI_USE_RESULT Error initGl();
};

/// @}

} // end namespace anki

#endif
