#ifndef ANKI_RESOURCE_MATERIAL_BUILDIN_VARIABLE_H
#define ANKI_RESOURCE_MATERIAL_BUILDIN_VARIABLE_H

#include "anki/resource/MaterialVariable.h"
#include "anki/util/ConstCharPtrHashMap.h"
#include "anki/resource/ShaderProgramUniformVariable.h"
#include <boost/array.hpp>


namespace anki {


/// XXX
class MaterialBuildinVariable: public MaterialVariable
{
	public:
		/// Standard attribute variables that are acceptable inside the
		/// ShaderProgram
		enum MatchingVariable
		{
			// Attributes
			MV_POSITION,
			MV_TANGENT,
			MV_NORMAL,
			MV_TEX_COORDS,
			// Uniforms
			// Matrices
			MV_MODEL_MAT,
			MV_VIEW_MAT,
			MV_PROJECTION_MAT,
			MV_MODELVIEW_MAT,
			MV_VIEWPROJECTION_MAT,
			MV_NORMAL_MAT,
			MV_MODELVIEWPROJECTION_MAT,
			// FAIs (for materials in blending stage)
			MV_MS_NORMAL_FAI,
			MV_MS_DIFFUSE_FAI,
			MV_MS_SPECULAR_FAI,
			MV_MS_DEPTH_FAI,
			MV_IS_FAI,
			MV_PPS_PRE_PASS_FAI,
			MV_PPS_POST_PASS_FAI,
			// Other
			MV_RENDERER_SIZE,
			MV_SCENE_AMBIENT_COLOR,
			MV_BLURRING,
			// num
			MV_NUM ///< The number of all buildin variables
		};

		MaterialBuildinVariable(
			const char* shaderProgVarName,
			const ShaderPrograms& shaderProgsArr);

		MatchingVariable getMatchingVariable() const
		{
			return bEnum;
		}

		/// Uses static cast to get the uniform. It will fail if the variable
		/// is attribute
		const ShaderProgramUniformVariable&
			getShaderProgramUniformVariable(PassType p) const;

		static bool isBuildin(const char* name, MatchingVariable* var = NULL,
			GLenum* dataType = NULL);

	private:
		/// From string to MatchingVariable
		typedef ConstCharPtrHashMap<MatchingVariable>::Type
			StrToMatchingVariable;

		/// From MatchingVariable to GL type (GLenum)
		typedef boost::unordered_map<MatchingVariable, GLenum>
			MatchingVariableToGlType;

		/// Given a name of a variable find its MaterialBuildinVariable enum
		static StrToMatchingVariable strToMatchingVariable;

		/// Given a MaterialBuildinVariable enum it gives the GL type
		static MatchingVariableToGlType matchingVariableToGlType;

		MatchingVariable bEnum;
};


inline const ShaderProgramUniformVariable&
	MaterialBuildinVariable::getShaderProgramUniformVariable(PassType p) const
{
	ASSERT(getShaderProgramVariable(p).getType() ==
		ShaderProgramVariable::T_UNIFORM);
	return static_cast<const ShaderProgramUniformVariable&>(
		getShaderProgramVariable(p));
}


} // end namespace


#endif