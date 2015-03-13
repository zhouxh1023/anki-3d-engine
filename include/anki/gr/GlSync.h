// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_GL_GL_SYNC_H
#define ANKI_GL_GL_SYNC_H

#include "anki/gr/GlCommon.h"
#include "anki/util/Thread.h"

namespace anki {

/// @addtogroup opengl_private
/// @{

/// Sync with the client
class GlClientSync
{
public:
	GlClientSync()
	:	m_barrier(2)
	{}

	/// Wait 
	void wait();

private:
	Barrier m_barrier;
};
/// @}

} // end namespace anki

#endif
