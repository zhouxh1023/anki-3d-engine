// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_GR_GL_BUFFER_H
#define ANKI_GR_GL_BUFFER_H

#include "anki/gr/gl/GlObject.h"

namespace anki {

/// @addtogroup opengl_private
/// @{
	
/// A wrapper for OpenGL buffer objects (vertex arrays, texture buffers etc)
/// to prevent us from making idiotic errors. It's storage immutable
class BufferImpl: public GlObject
{
public:
	using Base = GlObject;

	/// Default
	BufferImpl(GrManager* manager)
	:	GlObject(manager)
	{}

	/// It deletes the BO
	~BufferImpl()
	{
		destroy();
	}

	/// Creates a new BO with the given parameters and checks if everything
	/// went OK. Throws exception if fails
	/// @param target Depends on the BO
	/// @param dataPtr Points to the data buffer to copy to the VGA memory.
	///		   Put NULL if you want just to allocate memory
	/// @param sizeInBytes The size of the buffer that we will allocate in bytes
	/// @param flags GL access flags
	void create(
		GLenum target, const void* dataPtr, U32 sizeInBytes, GLbitfield flags);

	GLenum getTarget() const
	{
		ANKI_ASSERT(isCreated());
		return m_target;
	}

	void setTarget(GLenum target)
	{
		ANKI_ASSERT(isCreated());
		unbind(); // Unbind from the previous target
		m_target = target;
	}

	U32 getSize() const
	{
		ANKI_ASSERT(isCreated());
		return m_size;
	}

	/// Return the prersistent mapped address
	void* getPersistentMappingAddress()
	{
		ANKI_ASSERT(isCreated());
		ANKI_ASSERT(m_persistentMapping);
		return m_persistentMapping;
	}

	/// Bind
	void bind() const
	{
		ANKI_ASSERT(isCreated());
		glBindBuffer(m_target, m_glName);
	}

	/// Unbind BO
	void unbind() const
	{
		ANKI_ASSERT(isCreated());
		bindDefault(m_target);
	}

	/// Bind the default to a target
	static void bindDefault(GLenum target)
	{
		glBindBuffer(target, 0);
	}

	/// Write data to buffer. 
	/// @param[in] buff The buffer to copy to BO
	void write(const void* buff)
	{
		write(buff, 0, m_size);
	}

	/// The same as the other write but it maps only a subset of the data
	/// @param[in] buff The buffer to copy to BO
	/// @param[in] offset The offset
	/// @param[in] size The size in bytes we want to write
	void write(const void* buff, U32 offset, U32 size);

	/// Set the binding for this buffer
	void setBinding(GLuint binding) const;

	/// Set the binding point of this buffer with range
	void setBindingRange(GLuint binding, PtrSize offset, PtrSize size) const;

private:
	GLenum m_target = GL_NONE; ///< eg GL_TEXTURE_BUFFER 
	U32 m_size = 0; ///< The size of the buffer
	void* m_persistentMapping = nullptr;

	/// Delete the BO
	void destroy();
};
/// @}

} // end namespace anki

#endif
