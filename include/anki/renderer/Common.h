// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_RENDERER_COMMON_H
#define ANKI_RENDERER_COMMON_H

#include "anki/Gr.h"
#include "anki/util/Ptr.h"

namespace anki {

// Forward
class Renderer;
class Ms;
class Is;
class Fs;
class Lf;
class Ssao;
class Sslr;
class Sslf;
class Tm;
class Bloom;
class Pps;
class Dbg;
class Tiler;

/// Cut the job submition into multiple chains. We want to avoid feeding
/// GL with a huge job chain
const U RENDERER_COMMAND_BUFFERS_COUNT = 2;

// Render target formats
const U MS_COLOR_ATTACHMENTS_COUNT = 3;

const Array<PixelFormat, MS_COLOR_ATTACHMENTS_COUNT>
	MS_COLOR_ATTACHMENTS_PIXEL_FORMAT = {{
	{ComponentFormat::R8G8B8A8, TransformFormat::UNORM, false},
	{ComponentFormat::R8G8B8A8, TransformFormat::UNORM, false},
	{ComponentFormat::R8G8B8A8, TransformFormat::UNORM, false}}};

const PixelFormat MS_DEPTH_STENCIL_ATTACHMENT_FORMAT = {
	ComponentFormat::D24, TransformFormat::FLOAT, false};

const PixelFormat FS_COLOR_ATTACHMENT_FORMAT = {
	ComponentFormat::R8G8B8, TransformFormat::UNORM, false};

} // end namespace anki

#endif
