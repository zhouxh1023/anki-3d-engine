// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_RENDERER_LF_H
#define ANKI_RENDERER_LF_H

#include "anki/renderer/RenderingPass.h"
#include "anki/Gr.h"
#include "anki/resource/ShaderResource.h"
#include "anki/resource/TextureResource.h"

namespace anki {

/// @addtogroup renderer
/// @{

/// Lens flare rendering pass
class Lf: public RenderingPass
{
public:
	/// @privatesection
	/// @{
	Lf(Renderer* r)
	:	RenderingPass(r)
	{}

	~Lf();

	ANKI_USE_RESULT Error init(const ConfigSet& config);

	void runOcclusionTests(CommandBufferPtr& cmdb);

	void run(CommandBufferPtr& cmdb);
	/// @}

private:
	// Occlusion query
	Array<BufferPtr, 3> m_positionsVertBuff;
	BufferPtr m_mvpBuff;
	ShaderResourcePointer m_occlusionVert;
	ShaderResourcePointer m_occlusionFrag;
	PipelinePtr m_occlusionPpline;

	// Sprite billboards
	ShaderResourcePointer m_realVert;
	ShaderResourcePointer m_realFrag;
	PipelinePtr m_realPpline;
	Array<BufferPtr, 3> m_flareDataBuff;
	U32 m_flareSize;
	U8 m_maxSpritesPerFlare;
	U8 m_maxFlares;
	

	ANKI_USE_RESULT Error initSprite(const ConfigSet& config);
	ANKI_USE_RESULT Error initOcclusion(const ConfigSet& config);

	ANKI_USE_RESULT Error initInternal(const ConfigSet& initializer);
};
/// @}

} // end namespace anki

#endif
