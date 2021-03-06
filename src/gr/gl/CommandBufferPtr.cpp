// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include "anki/gr/CommandBufferPtr.h"
#include "anki/gr/gl/CommandBufferImpl.h"
#include "anki/gr/GrManager.h"
#include "anki/gr/gl/GrManagerImpl.h"
#include "anki/gr/gl/RenderingThread.h"
#include "anki/gr/gl/FramebufferImpl.h"
#include "anki/gr/TexturePtr.h"
#include "anki/gr/gl/TextureImpl.h"
#include "anki/gr/BufferPtr.h"
#include "anki/gr/gl/BufferImpl.h"
#include "anki/gr/OcclusionQueryPtr.h"
#include "anki/gr/gl/OcclusionQueryImpl.h"
#include "anki/core/Counters.h"
#include <utility>

namespace anki {

//==============================================================================
// Macros because we are bored to type
#define ANKI_STATE_CMD_0(type_, glfunc_) \
	class Command final: public GlCommand \
	{ \
	public: \
		Command() = default \
		Error operator()(CommandBufferImpl*) \
		{ \
			glfunc_(); \
			return ErrorCode::NONE; \
		} \
	}; \
	get().pushBackNewCommand<Command>(value_)

#define ANKI_STATE_CMD_1(type_, glfunc_, value_) \
	class Command: public GlCommand \
	{ \
	public: \
		type_ m_value; \
		Command(type_ v) \
		:	m_value(v) \
		{} \
		Error operator()(CommandBufferImpl*) \
		{ \
			glfunc_(m_value); \
			return ErrorCode::NONE; \
		} \
	}; \
	get().pushBackNewCommand<Command>(value_)

#define ANKI_STATE_CMD_2(type_, glfunc_, a_, b_) \
	class Command: public GlCommand \
	{ \
	public: \
		Array<type_, 2> m_value; \
		Command(type_ a, type_ b) \
		{ \
			m_value = {{a, b}}; \
		} \
		Error operator()(CommandBufferImpl*) \
		{ \
			glfunc_(m_value[0], m_value[1]); \
			return ErrorCode::NONE; \
		} \
	}; \
	get().pushBackNewCommand<Command>(a_, b_)

#define ANKI_STATE_CMD_3(type_, glfunc_, a_, b_, c_) \
	class Command: public GlCommand \
	{ \
	public: \
		Array<type_, 3> m_value; \
		Command(type_ a, type_ b, type_ c) \
		{ \
			m_value = {{a, b, c}}; \
		} \
		Error operator()(CommandBufferImpl*) \
		{ \
			glfunc_(m_value[0], m_value[1], m_value[2]); \
			return ErrorCode::NONE; \
		} \
	}; \
	get().pushBackNewCommand<Command>(a_, b_, c_)

#define ANKI_STATE_CMD_4(type_, glfunc_, a_, b_, c_, d_) \
	class Command: public GlCommand \
	{ \
	public: \
		Array<type_, 4> m_value; \
		Command(type_ a, type_ b, type_ c, type_ d) \
		{ \
			m_value = {{a, b, c, d}}; \
		} \
		Error operator()(CommandBufferImpl*) \
		{ \
			glfunc_(m_value[0], m_value[1], m_value[2], m_value[3]); \
			return ErrorCode::NONE; \
		} \
	}; \
	get().pushBackNewCommand<Command>(a_, b_, c_, d_)

#define ANKI_STATE_CMD_ENABLE(enum_, enable_) \
	class Command: public GlCommand \
	{ \
	public: \
		Bool8 m_enable; \
		Command(Bool enable) \
		:	m_enable(enable) \
		{} \
		Error operator()(CommandBufferImpl*) \
		{ \
			if(m_enable) \
			{ \
				glEnable(enum_); \
			} \
			else \
			{ \
				glDisable(enum_); \
			} \
			return ErrorCode::NONE; \
		} \
	}; \
	get().pushBackNewCommand<Command>(enable_)

//==============================================================================
CommandBufferPtr::CommandBufferPtr()
{}

//==============================================================================
CommandBufferPtr::~CommandBufferPtr()
{}

//==============================================================================
void CommandBufferPtr::create(GrManager* manager, CommandBufferInitHints hints)
{
	ANKI_ASSERT(!isCreated());
	ANKI_ASSERT(manager);

	Base::create(*manager);
	get().create(hints);
}

//==============================================================================
CommandBufferInitHints CommandBufferPtr::computeInitHints() const
{
	return get().computeInitHints();
}

//==============================================================================
void CommandBufferPtr::pushBackUserCommand(
	UserCallback callback, void* data)
{
	class Command: public GlCommand
	{
	public:
		UserCallback m_callback;
		void* m_userData;

		Command(UserCallback callback, void* userData)
		:	m_callback(callback),
			m_userData(userData)
		{
			ANKI_ASSERT(m_callback);
		}

		Error operator()(CommandBufferImpl* commands)
		{
			return (*m_callback)(m_userData);
		}
	};

	get().pushBackNewCommand<Command>(callback, data);
}

//==============================================================================
void CommandBufferPtr::pushBackOtherCommandBuffer(
	CommandBufferPtr& commands)
{
	class Command: public GlCommand
	{
	public:
		CommandBufferPtr m_commands;

		Command(CommandBufferPtr& commands)
		:	m_commands(commands)
		{}

		Error operator()(CommandBufferImpl*)
		{
			return m_commands.get().executeAllCommands();
		}
	};

	commands.get().makeImmutable();
	get().pushBackNewCommand<Command>(commands);
}

//==============================================================================
void CommandBufferPtr::flush()
{
	get().getManager().getImplementation().
		getRenderingThread().flushCommandBuffer(*this);
}

//==============================================================================
void CommandBufferPtr::finish()
{
	get().getManager().getImplementation().getRenderingThread().
		finishCommandBuffer(*this);
}

//==============================================================================
void CommandBufferPtr::setViewport(U16 minx, U16 miny, U16 maxx, U16 maxy)
{
	class Command: public GlCommand
	{
	public:
		Array<U16, 4> m_value;

		Command(U16 a, U16 b, U16 c, U16 d)
		{
			m_value = {{a, b, c, d}};
		}

		Error operator()(CommandBufferImpl* commands)
		{
			GlState& state = commands->getManager().getImplementation().
				getRenderingThread().getState();

			if(state.m_viewport[0] != m_value[0]
				|| state.m_viewport[1] != m_value[1]
				|| state.m_viewport[2] != m_value[2]
				|| state.m_viewport[3] != m_value[3])
			{
				glViewport(m_value[0], m_value[1], m_value[2], m_value[3]);

				state.m_viewport = m_value;
			}

			return ErrorCode::NONE;
		}
	};

	get().pushBackNewCommand<Command>(minx, miny, maxx, maxy);
}

//==============================================================================
void CommandBufferPtr::setColorWriteMask(
	Bool red, Bool green, Bool blue, Bool alpha)
{
	ANKI_STATE_CMD_4(Bool8, glColorMask, red, green, blue, alpha);
}

//==============================================================================
void CommandBufferPtr::enableDepthTest(Bool enable)
{
	ANKI_STATE_CMD_ENABLE(GL_DEPTH_TEST, enable);
}

//==============================================================================
void CommandBufferPtr::setDepthFunction(GLenum func)
{
	ANKI_STATE_CMD_1(GLenum, glDepthFunc, func);
}

//==============================================================================
void CommandBufferPtr::setDepthWriteMask(Bool write)
{
	ANKI_STATE_CMD_1(Bool8, glDepthMask, write);
}

//==============================================================================
void CommandBufferPtr::enableStencilTest(Bool enable)
{
	ANKI_STATE_CMD_ENABLE(GL_STENCIL_TEST, enable);
}

//==============================================================================
void CommandBufferPtr::setStencilFunction(
	GLenum function, U32 reference, U32 mask)
{
	ANKI_STATE_CMD_3(U32, glStencilFunc, function, reference, mask);
}

//==============================================================================
void CommandBufferPtr::setStencilPlaneMask(U32 mask)
{
	ANKI_STATE_CMD_1(U32, glStencilMask, mask);
}

//==============================================================================
void CommandBufferPtr::setStencilOperations(GLenum stencFail, GLenum depthFail,
	GLenum depthPass)
{
	ANKI_STATE_CMD_3(GLenum, glStencilOp, stencFail, depthFail, depthPass);
}

//==============================================================================
void CommandBufferPtr::enableBlend(Bool enable)
{
	ANKI_STATE_CMD_ENABLE(GL_BLEND, enable);
}

//==============================================================================
void CommandBufferPtr::setBlendEquation(GLenum equation)
{
	ANKI_STATE_CMD_1(GLenum, glBlendEquation, equation);
}

//==============================================================================
void CommandBufferPtr::setBlendFunctions(GLenum sfactor, GLenum dfactor)
{
	class Command: public GlCommand
	{
	public:
		GLenum m_sfactor;
		GLenum m_dfactor;

		Command(GLenum sfactor, GLenum dfactor)
			: m_sfactor(sfactor), m_dfactor(dfactor)
		{}

		Error operator()(CommandBufferImpl* commands)
		{
			GlState& state = commands->getManager().getImplementation().
				getRenderingThread().getState();

			if(state.m_blendSfunc != m_sfactor
				|| state.m_blendDfunc != m_dfactor)
			{
				glBlendFunc(m_sfactor, m_dfactor);

				state.m_blendSfunc = m_sfactor;
				state.m_blendDfunc = m_dfactor;
			}

			return ErrorCode::NONE;
		}
	};

	get().pushBackNewCommand<Command>(sfactor, dfactor);
}

//==============================================================================
void CommandBufferPtr::setBlendColor(F32 r, F32 g, F32 b, F32 a)
{
	ANKI_STATE_CMD_4(F32, glBlendColor, r, g, b, a);
}

//==============================================================================
void CommandBufferPtr::enablePrimitiveRestart(Bool enable)
{
	ANKI_STATE_CMD_ENABLE(GL_PRIMITIVE_RESTART, enable);
}

//==============================================================================
void CommandBufferPtr::setPatchVertexCount(U32 count)
{
	ANKI_STATE_CMD_2(GLint, glPatchParameteri, GL_PATCH_VERTICES, count);
}

//==============================================================================
void CommandBufferPtr::enableCulling(Bool enable)
{
	ANKI_STATE_CMD_ENABLE(GL_CULL_FACE, enable);
}

//==============================================================================
void CommandBufferPtr::setCullFace(GLenum mode)
{
	ANKI_STATE_CMD_1(GLenum, glCullFace, mode);
}

//==============================================================================
void CommandBufferPtr::setPolygonOffset(F32 factor, F32 units)
{
	ANKI_STATE_CMD_2(F32, glPolygonOffset, factor, units);
}

//==============================================================================
void CommandBufferPtr::enablePolygonOffset(Bool enable)
{
	ANKI_STATE_CMD_ENABLE(GL_POLYGON_OFFSET_FILL, enable);
}

//==============================================================================
void CommandBufferPtr::setPolygonMode(GLenum face, GLenum mode)
{
	ANKI_STATE_CMD_2(GLenum, glPolygonMode, face, mode);
}

//==============================================================================
void CommandBufferPtr::enablePointSize(Bool enable)
{
	ANKI_STATE_CMD_ENABLE(GL_PROGRAM_POINT_SIZE, enable);
}

//==============================================================================
class BindTexturesCommand: public GlCommand
{
public:
	static const U MAX_BIND_TEXTURES = 8;

	Array<TexturePtr, MAX_BIND_TEXTURES> m_texes;
	U32 m_texCount;
	U32 m_first;

	BindTexturesCommand(
		TexturePtr textures[], U count, U32 first)
	:	m_first(first)
	{
		m_texCount = count;
		TexturePtr* t = textures;
		while(count-- != 0)
		{
			m_texes[count] = *t;
			++t;
		}
	}

	Error operator()(CommandBufferImpl* commands)
	{
		Array<GLuint, MAX_BIND_TEXTURES> names;

		U count = m_texCount;
		U i = 0;
		while(count-- != 0)
		{
			names[i++] = m_texes[count].get().getGlName();
		}

		glBindTextures(m_first, m_texCount, &names[0]);

		return ErrorCode::NONE;
	}
};

void CommandBufferPtr::bindTextures(U32 first,
	TexturePtr textures[], U32 count)
{
	ANKI_ASSERT(count > 0);

	get().pushBackNewCommand<BindTexturesCommand>(&textures[0], count, first);
}

//==============================================================================
class DrawElementsCondCommand: public GlCommand
{
public:
	GLenum m_mode;
	U8 m_indexSize;
	GlDrawElementsIndirectInfo m_info;
	OcclusionQueryPtr m_query;

	DrawElementsCondCommand(
		GLenum mode,
		U8 indexSize,
		GlDrawElementsIndirectInfo& info,
		OcclusionQueryPtr query = OcclusionQueryPtr())
	:	m_mode(mode),
		m_indexSize(indexSize),
		m_info(info),
		m_query(query)
	{}

	Error operator()(CommandBufferImpl*)
	{
		ANKI_ASSERT(m_indexSize != 0);

		GLenum indicesType = 0;
		switch(m_indexSize)
		{
		case 1:
			indicesType = GL_UNSIGNED_BYTE;
			break;
		case 2:
			indicesType = GL_UNSIGNED_SHORT;
			break;
		case 4:
			indicesType = GL_UNSIGNED_INT;
			break;
		default:
			ANKI_ASSERT(0);
			break;
		};

		if(!m_query.isCreated() || !m_query.get().skipDrawcall())
		{
			glDrawElementsInstancedBaseVertexBaseInstance(
				m_mode,
				m_info.m_count,
				indicesType,
				(const void*)(PtrSize)(m_info.m_firstIndex * m_indexSize),
				m_info.m_instanceCount,
				m_info.m_baseVertex,
				m_info.m_baseInstance);

			ANKI_COUNTER_INC(GL_DRAWCALLS_COUNT, (U64)1);
		}

		return ErrorCode::NONE;
	}
};

void CommandBufferPtr::drawElements(
	GLenum mode, U8 indexSize, U32 count, U32 instanceCount, U32 firstIndex,
	U32 baseVertex, U32 baseInstance)
{
	GlDrawElementsIndirectInfo info(count, instanceCount, firstIndex,
		baseVertex, baseInstance);

	get().pushBackNewCommand<DrawElementsCondCommand>(mode, indexSize, info);
}

//==============================================================================
class DrawArraysCondCommand: public GlCommand
{
public:
	GLenum m_mode;
	GlDrawArraysIndirectInfo m_info;
	OcclusionQueryPtr m_query;

	DrawArraysCondCommand(
		GLenum mode,
		GlDrawArraysIndirectInfo& info,
		OcclusionQueryPtr query = OcclusionQueryPtr())
	:	m_mode(mode),
		m_info(info),
		m_query(query)
	{}

	Error operator()(CommandBufferImpl*)
	{
		if(!m_query.isCreated() || !m_query.get().skipDrawcall())
		{
			glDrawArraysInstancedBaseInstance(
				m_mode,
				m_info.m_first,
				m_info.m_count,
				m_info.m_instanceCount,
				m_info.m_baseInstance);

			ANKI_COUNTER_INC(GL_DRAWCALLS_COUNT, (U64)1);
		}

		return ErrorCode::NONE;
	}
};

void CommandBufferPtr::drawArrays(
	GLenum mode, U32 count, U32 instanceCount, U32 first, U32 baseInstance)
{
	GlDrawArraysIndirectInfo info(count, instanceCount, first, baseInstance);

	get().pushBackNewCommand<DrawArraysCondCommand>(mode, info);
}

//==============================================================================
void CommandBufferPtr::drawElementsConditional(
	OcclusionQueryPtr& query,
	GLenum mode, U8 indexSize, U32 count, U32 instanceCount, U32 firstIndex,
	U32 baseVertex, U32 baseInstance)
{
	GlDrawElementsIndirectInfo info(count, instanceCount, firstIndex,
		baseVertex, baseInstance);

	get().pushBackNewCommand<DrawElementsCondCommand>(mode, indexSize, info, query);
}

//==============================================================================
void CommandBufferPtr::drawArraysConditional(
	OcclusionQueryPtr& query,
	GLenum mode, U32 count, U32 instanceCount, U32 first, U32 baseInstance)
{
	GlDrawArraysIndirectInfo info(count, instanceCount, first, baseInstance);

	get().pushBackNewCommand<DrawArraysCondCommand>(mode, info, query);
}

//==============================================================================
class CopyBuffTex: public GlCommand
{
public:
	TexturePtr m_tex;
	BufferPtr m_buff;

	CopyBuffTex(TexturePtr& from, BufferPtr& to)
	:	m_tex(from),
		m_buff(to)
	{}

	Error operator()(CommandBufferImpl* cmd)
	{
		TextureImpl& tex = m_tex.get();
		BufferImpl& buff = m_buff.get();

		// Bind
		GLuint copyFbo = cmd->getManager().getImplementation().
			getRenderingThread().getCopyFbo();
		glBindFramebuffer(GL_FRAMEBUFFER, copyFbo);

		// Attach texture
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			tex.getTarget(), tex.getGlName(), 0);

		// Set draw buffers
		GLuint drawBuff = GL_COLOR_ATTACHMENT0;
		glDrawBuffers(1, &drawBuff);

		// Bind buffer
		ANKI_ASSERT(m_buff.getTarget() == GL_PIXEL_PACK_BUFFER);
		buff.bind();

		// Read pixels
		GLuint format = GL_NONE, type = GL_NONE;
		if(tex.getInternalFormat() == GL_RG32UI)
		{
			format = GL_RG_INTEGER;
			type = GL_UNSIGNED_INT;
		}
		else if(tex.getInternalFormat() == GL_RG32F)
		{
			format = GL_RG;
			type = GL_FLOAT;
		}
		else
		{
			ANKI_ASSERT(0 && "Not implemented");
		}

		glReadPixels(0, 0, tex.getWidth(), tex.getHeight(),
			format, type, nullptr);

		// End
		buff.unbind();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return ErrorCode::NONE;
	}
};

void CommandBufferPtr::copyTextureToBuffer(
	TexturePtr& from, BufferPtr& to)
{
	get().pushBackNewCommand<CopyBuffTex>(from, to);
}

//==============================================================================
class DispatchCommand: public GlCommand
{
public:
	Array<U32, 3> m_size;

	DispatchCommand(U32 x, U32 y, U32 z)
	:	m_size({x, y, z})
	{}

	Error operator()(CommandBufferImpl*)
	{
		glDispatchCompute(m_size[0], m_size[1], m_size[2]);
		return ErrorCode::NONE;
	}
};

void CommandBufferPtr::dispatchCompute(
	U32 groupCountX, U32 groupCountY, U32 groupCountZ)
{
	get().pushBackNewCommand<DispatchCommand>(
		groupCountX, groupCountY, groupCountZ);
}

//==============================================================================
class UpdateUniformsCommand final: public GlCommand
{
public:
	GLuint m_uboName;
	U32 m_offset;
	U16 m_range;

	UpdateUniformsCommand(GLuint ubo, U32 offset, U16 range)
	:	m_uboName(ubo),
		m_offset(offset),
		m_range(range)
	{}

	Error operator()(CommandBufferImpl*)
	{
		const U binding = 0;
		glBindBufferRange(
			GL_UNIFORM_BUFFER, binding, m_uboName, m_offset, m_range);

		return ErrorCode::NONE;
	}
};

void CommandBufferPtr::updateDynamicUniforms(void* data, U32 originalSize)
{
	ANKI_ASSERT(data);
	ANKI_ASSERT(originalSize > 0);
	ANKI_ASSERT(originalSize <= 1024 * 4 && "Too high?");

	GlState& state =
		get().getManager().getImplementation().getRenderingThread().getState();

	const U uboSize = state.m_globalUboSize;
	const U subUboSize = GlState::MAX_UBO_SIZE;

	// Get offset in the contiguous buffer
	U size = getAlignedRoundUp(state.m_uniBuffOffsetAlignment, originalSize);
	U offset = state.m_globalUboCurrentOffset.fetchAdd(size);
	offset = offset % uboSize;

	while((offset % subUboSize) + size > subUboSize)
	{
		// Update area will fall between UBOs, need to start over
		offset = state.m_globalUboCurrentOffset.fetchAdd(size);
		offset = offset % uboSize;
	}

	ANKI_ASSERT(isAligned(state.m_uniBuffOffsetAlignment, offset));
	ANKI_ASSERT(offset + size <= uboSize);

	// Get actual UBO address to write
	U uboIdx = offset / subUboSize;
	U subUboOffset = offset % subUboSize;
	ANKI_ASSERT(isAligned(state.m_uniBuffOffsetAlignment, subUboOffset));

	U8* addressToWrite = state.m_globalUboAddresses[uboIdx] + subUboOffset;

	// Write
	memcpy(addressToWrite, data, originalSize);

	// Push bind command
	get().pushBackNewCommand<UpdateUniformsCommand>(
		state.m_globalUbos[uboIdx], subUboOffset, originalSize);
}

} // end namespace anki
