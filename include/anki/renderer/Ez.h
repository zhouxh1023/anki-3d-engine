// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_RENDERER_EZ_H
#define ANKI_RENDERER_EZ_H

#include "anki/renderer/RenderingPass.h"
#include "anki/Gr.h"

namespace anki {

/// @addtogroup renderer
/// @{

/// Material stage EarlyZ pass
class Ez: public RenderingPass
{
	friend class Ms;

private:
	U32 m_maxObjectsToDraw;

	Ez(Renderer* r)
	:	RenderingPass(r)
	{}

	ANKI_USE_RESULT Error init(const ConfigSet& initializer);
	ANKI_USE_RESULT Error run(CommandBufferPtr& cmdBuff);
};
/// @}

} // end namespace anki

#endif
