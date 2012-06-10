#include "anki/gl/Vao.h"
#include "anki/gl/Vbo.h"
#include "anki/util/Exception.h"
#include "anki/gl/ShaderProgram.h"

namespace anki {

//==============================================================================

std::atomic<uint32_t> Vao::counter(0);

//==============================================================================
Vao::~Vao()
{
	if(isCreated())
	{
		destroy();
	}
}

//==============================================================================
void Vao::attachArrayBufferVbo(const Vbo& vbo, GLuint attribVarLocation,
	GLint size, GLenum type, GLboolean normalized, GLsizei stride,
	const GLvoid* pointer)
{
	ANKI_ASSERT(isCreated());
	ANKI_ASSERT(vbo.getBufferTarget() == GL_ARRAY_BUFFER
		&& "Only GL_ARRAY_BUFFER is accepted");

	GLuint prevVao = getCurrentVertexArrayBinding();
	
	bind();
	vbo.bind();
	glVertexAttribPointer(attribVarLocation, size, type, normalized,
		stride, pointer);
	glEnableVertexAttribArray(attribVarLocation);
	vbo.unbind();
	unbind();

	glBindVertexArray(prevVao);

	ANKI_CHECK_GL_ERROR();
}

//==============================================================================
void Vao::attachArrayBufferVbo(const Vbo& vbo,
	const ShaderProgramAttributeVariable& attribVar,
	GLint size, GLenum type, GLboolean normalized, GLsizei stride,
	const GLvoid* pointer)
{
	attachArrayBufferVbo(vbo, attribVar.getLocation(), size, type, normalized,
		stride, pointer);
}

//==============================================================================
void Vao::attachElementArrayBufferVbo(const Vbo& vbo)
{
	ANKI_ASSERT(isCreated());
	ANKI_ASSERT(vbo.getBufferTarget() == GL_ELEMENT_ARRAY_BUFFER
		&& "Only GL_ELEMENT_ARRAY_BUFFER is accepted");

	GLuint prevVao = getCurrentVertexArrayBinding();
	bind();
	vbo.bind();
	unbind();
	glBindVertexArray(prevVao);
	ANKI_CHECK_GL_ERROR();
}

} // end namespace