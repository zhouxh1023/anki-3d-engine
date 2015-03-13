// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_GR_GL_OBJECT_H
#define ANKI_GR_GL_OBJECT_H

#include "anki/gr/GlCommon.h"

namespace anki {

/// @addtogroup opengl_private
/// @{

/// A GL object
class GlObject: public NonCopyable
{
public:
	/// Default
	GlObject()
	:	m_glName(0)
	{}

	~GlObject()
	{
		// The destructor of the derived GL object should pass 0 name
		ANKI_ASSERT(!isCreated());
	}

	/// Get the GL name for the current frame
	GLuint getGlName() const
	{
		ANKI_ASSERT(isCreated());
		return m_glName;
	}

	/// GL object is created
	Bool isCreated() const
	{
		return m_glName != 0;
	}

protected:
	GLuint m_glName; ///< OpenGL name
};
/// @}

} // end namespace anki

#endif