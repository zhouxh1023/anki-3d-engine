// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_GR_GL_TEXTURE_IMPL_H
#define ANKI_GR_GL_TEXTURE_IMPL_H

#include "anki/gr/gl/GlObject.h"
#include "anki/util/Array.h"

namespace anki {

/// @addtogroup opengl
/// @{

/// Texture container
class TextureImpl: public GlObject
{
public:
	using Base = GlObject;
	using Initializer = TextureInitializer;

	TextureImpl(GrManager* manager)
	:	Base(manager)
	{}

	~TextureImpl()
	{
		destroy();
	}

	/// Create a texture
	void create(const Initializer& init);

	GLenum getInternalFormat() const
	{
		ANKI_ASSERT(isCreated());
		return m_internalFormat;
	}

	GLenum getTarget() const
	{
		ANKI_ASSERT(isCreated());
		return m_target;
	}

	U32 getWidth() const
	{
		ANKI_ASSERT(isCreated());
		return m_width;
	}

	U32 getHeight() const
	{
		ANKI_ASSERT(isCreated());
		return m_height;
	}

	U32 getDepth() const
	{
		ANKI_ASSERT(isCreated());
		return m_depth;
	}

	/// Bind the texture to a specified unit
	void bind(U32 unit) const;

	/// Generate mipmaps
	void generateMipmaps();

private:
	GLenum m_target = GL_NONE; ///< GL_TEXTURE_2D, GL_TEXTURE_3D... etc
	GLenum m_internalFormat = GL_NONE; ///< GL_COMPRESSED_RED, GL_RGB16 etc
	GLenum m_format = GL_NONE;
	GLenum m_type = GL_NONE;
	U32 m_width = 0;
	U32 m_height = 0;
	U32 m_depth = 0;
	U8 m_mipsCount = 0;
	Bool8 m_compressed = false;

	void destroy();

	static U32 computeMaxMipmapCount(U32 w, U32 h);
};
/// @}

} // end namespace anki

#endif
