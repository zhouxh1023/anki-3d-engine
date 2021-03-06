// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

// WARNING: The file is auto generated.

#include "anki/script/LuaBinder.h"
#include "anki/script/ScriptManager.h"
#include "anki/Scene.h"

namespace anki {

//==============================================================================
template<typename T, typename... TArgs>
static T* newSceneNode(SceneGraph* scene, CString name, TArgs... args)
{
	T* ptr;
	Error err = scene->template newSceneNode<T>(
		name, ptr, args...);

	if(!err)
	{
		return ptr;
	}
	else
	{
		return nullptr;
	}
}

//==============================================================================
static SceneGraph* getSceneGraph(lua_State* l)
{
	LuaBinder* binder = nullptr;
	lua_getallocf(l, reinterpret_cast<void**>(&binder));

	ScriptManager* scriptManager =
		reinterpret_cast<ScriptManager*>(binder->getParent());

	return &scriptManager->_getSceneGraph();
}

//==============================================================================
// MoveComponent                                                               =
//==============================================================================

//==============================================================================
static const char* classnameMoveComponent = "MoveComponent";

template<>
I64 LuaBinder::getWrappedTypeSignature<MoveComponent>()
{
	return 2038493110845313445;
}

template<>
const char* LuaBinder::getWrappedTypeName<MoveComponent>()
{
	return classnameMoveComponent;
}

//==============================================================================
/// Pre-wrap method MoveComponent::setLocalOrigin.
static inline int pwrapMoveComponentsetLocalOrigin(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameMoveComponent, 2038493110845313445, ud)) return -1;
	MoveComponent* self = static_cast<MoveComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	if(LuaBinder::checkUserData(l, 2, "Vec4", 6804478823655046386, ud)) return -1;
	Vec4* iarg0 = static_cast<Vec4*>(ud->m_data);
	const Vec4& arg0(*iarg0);
	
	// Call the method
	self->setLocalOrigin(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method MoveComponent::setLocalOrigin.
static int wrapMoveComponentsetLocalOrigin(lua_State* l)
{
	int res = pwrapMoveComponentsetLocalOrigin(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method MoveComponent::getLocalOrigin.
static inline int pwrapMoveComponentgetLocalOrigin(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameMoveComponent, 2038493110845313445, ud)) return -1;
	MoveComponent* self = static_cast<MoveComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	const Vec4& ret = self->getLocalOrigin();
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "Vec4");
	ud->m_data = const_cast<void*>(static_cast<const void*>(&ret));
	ud->m_gc = false;
	ud->m_sig = 6804478823655046386;
	
	return 1;
}

//==============================================================================
/// Wrap method MoveComponent::getLocalOrigin.
static int wrapMoveComponentgetLocalOrigin(lua_State* l)
{
	int res = pwrapMoveComponentgetLocalOrigin(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method MoveComponent::setLocalRotation.
static inline int pwrapMoveComponentsetLocalRotation(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameMoveComponent, 2038493110845313445, ud)) return -1;
	MoveComponent* self = static_cast<MoveComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	if(LuaBinder::checkUserData(l, 2, "Mat3x4", -2654194732934255869, ud)) return -1;
	Mat3x4* iarg0 = static_cast<Mat3x4*>(ud->m_data);
	const Mat3x4& arg0(*iarg0);
	
	// Call the method
	self->setLocalRotation(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method MoveComponent::setLocalRotation.
static int wrapMoveComponentsetLocalRotation(lua_State* l)
{
	int res = pwrapMoveComponentsetLocalRotation(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method MoveComponent::getLocalRotation.
static inline int pwrapMoveComponentgetLocalRotation(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameMoveComponent, 2038493110845313445, ud)) return -1;
	MoveComponent* self = static_cast<MoveComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	const Mat3x4& ret = self->getLocalRotation();
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "Mat3x4");
	ud->m_data = const_cast<void*>(static_cast<const void*>(&ret));
	ud->m_gc = false;
	ud->m_sig = -2654194732934255869;
	
	return 1;
}

//==============================================================================
/// Wrap method MoveComponent::getLocalRotation.
static int wrapMoveComponentgetLocalRotation(lua_State* l)
{
	int res = pwrapMoveComponentgetLocalRotation(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method MoveComponent::setLocalScale.
static inline int pwrapMoveComponentsetLocalScale(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameMoveComponent, 2038493110845313445, ud)) return -1;
	MoveComponent* self = static_cast<MoveComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	F32 arg0;
	if(LuaBinder::checkNumber(l, 2, arg0)) return -1;
	
	// Call the method
	self->setLocalScale(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method MoveComponent::setLocalScale.
static int wrapMoveComponentsetLocalScale(lua_State* l)
{
	int res = pwrapMoveComponentsetLocalScale(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method MoveComponent::getLocalScale.
static inline int pwrapMoveComponentgetLocalScale(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameMoveComponent, 2038493110845313445, ud)) return -1;
	MoveComponent* self = static_cast<MoveComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	F32 ret = self->getLocalScale();
	
	// Push return value
	lua_pushnumber(l, ret);
	
	return 1;
}

//==============================================================================
/// Wrap method MoveComponent::getLocalScale.
static int wrapMoveComponentgetLocalScale(lua_State* l)
{
	int res = pwrapMoveComponentgetLocalScale(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method MoveComponent::setLocalTransform.
static inline int pwrapMoveComponentsetLocalTransform(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameMoveComponent, 2038493110845313445, ud)) return -1;
	MoveComponent* self = static_cast<MoveComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	if(LuaBinder::checkUserData(l, 2, "Transform", 7048620195620777229, ud)) return -1;
	Transform* iarg0 = static_cast<Transform*>(ud->m_data);
	const Transform& arg0(*iarg0);
	
	// Call the method
	self->setLocalTransform(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method MoveComponent::setLocalTransform.
static int wrapMoveComponentsetLocalTransform(lua_State* l)
{
	int res = pwrapMoveComponentsetLocalTransform(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method MoveComponent::getLocalTransform.
static inline int pwrapMoveComponentgetLocalTransform(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameMoveComponent, 2038493110845313445, ud)) return -1;
	MoveComponent* self = static_cast<MoveComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	const Transform& ret = self->getLocalTransform();
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "Transform");
	ud->m_data = const_cast<void*>(static_cast<const void*>(&ret));
	ud->m_gc = false;
	ud->m_sig = 7048620195620777229;
	
	return 1;
}

//==============================================================================
/// Wrap method MoveComponent::getLocalTransform.
static int wrapMoveComponentgetLocalTransform(lua_State* l)
{
	int res = pwrapMoveComponentgetLocalTransform(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class MoveComponent.
static inline void wrapMoveComponent(lua_State* l)
{
	LuaBinder::createClass(l, classnameMoveComponent);
	LuaBinder::pushLuaCFuncMethod(l, "setLocalOrigin", wrapMoveComponentsetLocalOrigin);
	LuaBinder::pushLuaCFuncMethod(l, "getLocalOrigin", wrapMoveComponentgetLocalOrigin);
	LuaBinder::pushLuaCFuncMethod(l, "setLocalRotation", wrapMoveComponentsetLocalRotation);
	LuaBinder::pushLuaCFuncMethod(l, "getLocalRotation", wrapMoveComponentgetLocalRotation);
	LuaBinder::pushLuaCFuncMethod(l, "setLocalScale", wrapMoveComponentsetLocalScale);
	LuaBinder::pushLuaCFuncMethod(l, "getLocalScale", wrapMoveComponentgetLocalScale);
	LuaBinder::pushLuaCFuncMethod(l, "setLocalTransform", wrapMoveComponentsetLocalTransform);
	LuaBinder::pushLuaCFuncMethod(l, "getLocalTransform", wrapMoveComponentgetLocalTransform);
	lua_settop(l, 0);
}

//==============================================================================
// LightComponent                                                              =
//==============================================================================

//==============================================================================
static const char* classnameLightComponent = "LightComponent";

template<>
I64 LuaBinder::getWrappedTypeSignature<LightComponent>()
{
	return 7940823622056993903;
}

template<>
const char* LuaBinder::getWrappedTypeName<LightComponent>()
{
	return classnameLightComponent;
}

//==============================================================================
/// Pre-wrap method LightComponent::setDiffuseColor.
static inline int pwrapLightComponentsetDiffuseColor(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	if(LuaBinder::checkUserData(l, 2, "Vec4", 6804478823655046386, ud)) return -1;
	Vec4* iarg0 = static_cast<Vec4*>(ud->m_data);
	const Vec4& arg0(*iarg0);
	
	// Call the method
	self->setDiffuseColor(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LightComponent::setDiffuseColor.
static int wrapLightComponentsetDiffuseColor(lua_State* l)
{
	int res = pwrapLightComponentsetDiffuseColor(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::getDiffuseColor.
static inline int pwrapLightComponentgetDiffuseColor(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	const Vec4& ret = self->getDiffuseColor();
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "Vec4");
	ud->m_data = const_cast<void*>(static_cast<const void*>(&ret));
	ud->m_gc = false;
	ud->m_sig = 6804478823655046386;
	
	return 1;
}

//==============================================================================
/// Wrap method LightComponent::getDiffuseColor.
static int wrapLightComponentgetDiffuseColor(lua_State* l)
{
	int res = pwrapLightComponentgetDiffuseColor(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::setSpecularColor.
static inline int pwrapLightComponentsetSpecularColor(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	if(LuaBinder::checkUserData(l, 2, "Vec4", 6804478823655046386, ud)) return -1;
	Vec4* iarg0 = static_cast<Vec4*>(ud->m_data);
	const Vec4& arg0(*iarg0);
	
	// Call the method
	self->setSpecularColor(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LightComponent::setSpecularColor.
static int wrapLightComponentsetSpecularColor(lua_State* l)
{
	int res = pwrapLightComponentsetSpecularColor(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::getSpecularColor.
static inline int pwrapLightComponentgetSpecularColor(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	const Vec4& ret = self->getSpecularColor();
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "Vec4");
	ud->m_data = const_cast<void*>(static_cast<const void*>(&ret));
	ud->m_gc = false;
	ud->m_sig = 6804478823655046386;
	
	return 1;
}

//==============================================================================
/// Wrap method LightComponent::getSpecularColor.
static int wrapLightComponentgetSpecularColor(lua_State* l)
{
	int res = pwrapLightComponentgetSpecularColor(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::setRadius.
static inline int pwrapLightComponentsetRadius(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	F32 arg0;
	if(LuaBinder::checkNumber(l, 2, arg0)) return -1;
	
	// Call the method
	self->setRadius(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LightComponent::setRadius.
static int wrapLightComponentsetRadius(lua_State* l)
{
	int res = pwrapLightComponentsetRadius(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::getRadius.
static inline int pwrapLightComponentgetRadius(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	F32 ret = self->getRadius();
	
	// Push return value
	lua_pushnumber(l, ret);
	
	return 1;
}

//==============================================================================
/// Wrap method LightComponent::getRadius.
static int wrapLightComponentgetRadius(lua_State* l)
{
	int res = pwrapLightComponentgetRadius(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::setDistance.
static inline int pwrapLightComponentsetDistance(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	F32 arg0;
	if(LuaBinder::checkNumber(l, 2, arg0)) return -1;
	
	// Call the method
	self->setDistance(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LightComponent::setDistance.
static int wrapLightComponentsetDistance(lua_State* l)
{
	int res = pwrapLightComponentsetDistance(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::getDistance.
static inline int pwrapLightComponentgetDistance(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	F32 ret = self->getDistance();
	
	// Push return value
	lua_pushnumber(l, ret);
	
	return 1;
}

//==============================================================================
/// Wrap method LightComponent::getDistance.
static int wrapLightComponentgetDistance(lua_State* l)
{
	int res = pwrapLightComponentgetDistance(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::setInnerAngle.
static inline int pwrapLightComponentsetInnerAngle(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	F32 arg0;
	if(LuaBinder::checkNumber(l, 2, arg0)) return -1;
	
	// Call the method
	self->setInnerAngle(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LightComponent::setInnerAngle.
static int wrapLightComponentsetInnerAngle(lua_State* l)
{
	int res = pwrapLightComponentsetInnerAngle(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::getInnerAngle.
static inline int pwrapLightComponentgetInnerAngle(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	F32 ret = self->getInnerAngle();
	
	// Push return value
	lua_pushnumber(l, ret);
	
	return 1;
}

//==============================================================================
/// Wrap method LightComponent::getInnerAngle.
static int wrapLightComponentgetInnerAngle(lua_State* l)
{
	int res = pwrapLightComponentgetInnerAngle(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::setOuterAngle.
static inline int pwrapLightComponentsetOuterAngle(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	F32 arg0;
	if(LuaBinder::checkNumber(l, 2, arg0)) return -1;
	
	// Call the method
	self->setOuterAngle(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LightComponent::setOuterAngle.
static int wrapLightComponentsetOuterAngle(lua_State* l)
{
	int res = pwrapLightComponentsetOuterAngle(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::getOuterAngle.
static inline int pwrapLightComponentgetOuterAngle(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	F32 ret = self->getOuterAngle();
	
	// Push return value
	lua_pushnumber(l, ret);
	
	return 1;
}

//==============================================================================
/// Wrap method LightComponent::getOuterAngle.
static int wrapLightComponentgetOuterAngle(lua_State* l)
{
	int res = pwrapLightComponentgetOuterAngle(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::setShadowEnabled.
static inline int pwrapLightComponentsetShadowEnabled(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	Bool arg0;
	if(LuaBinder::checkNumber(l, 2, arg0)) return -1;
	
	// Call the method
	self->setShadowEnabled(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LightComponent::setShadowEnabled.
static int wrapLightComponentsetShadowEnabled(lua_State* l)
{
	int res = pwrapLightComponentsetShadowEnabled(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LightComponent::getShadowEnabled.
static inline int pwrapLightComponentgetShadowEnabled(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLightComponent, 7940823622056993903, ud)) return -1;
	LightComponent* self = static_cast<LightComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	Bool ret = self->getShadowEnabled();
	
	// Push return value
	lua_pushboolean(l, ret);
	
	return 1;
}

//==============================================================================
/// Wrap method LightComponent::getShadowEnabled.
static int wrapLightComponentgetShadowEnabled(lua_State* l)
{
	int res = pwrapLightComponentgetShadowEnabled(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class LightComponent.
static inline void wrapLightComponent(lua_State* l)
{
	LuaBinder::createClass(l, classnameLightComponent);
	LuaBinder::pushLuaCFuncMethod(l, "setDiffuseColor", wrapLightComponentsetDiffuseColor);
	LuaBinder::pushLuaCFuncMethod(l, "getDiffuseColor", wrapLightComponentgetDiffuseColor);
	LuaBinder::pushLuaCFuncMethod(l, "setSpecularColor", wrapLightComponentsetSpecularColor);
	LuaBinder::pushLuaCFuncMethod(l, "getSpecularColor", wrapLightComponentgetSpecularColor);
	LuaBinder::pushLuaCFuncMethod(l, "setRadius", wrapLightComponentsetRadius);
	LuaBinder::pushLuaCFuncMethod(l, "getRadius", wrapLightComponentgetRadius);
	LuaBinder::pushLuaCFuncMethod(l, "setDistance", wrapLightComponentsetDistance);
	LuaBinder::pushLuaCFuncMethod(l, "getDistance", wrapLightComponentgetDistance);
	LuaBinder::pushLuaCFuncMethod(l, "setInnerAngle", wrapLightComponentsetInnerAngle);
	LuaBinder::pushLuaCFuncMethod(l, "getInnerAngle", wrapLightComponentgetInnerAngle);
	LuaBinder::pushLuaCFuncMethod(l, "setOuterAngle", wrapLightComponentsetOuterAngle);
	LuaBinder::pushLuaCFuncMethod(l, "getOuterAngle", wrapLightComponentgetOuterAngle);
	LuaBinder::pushLuaCFuncMethod(l, "setShadowEnabled", wrapLightComponentsetShadowEnabled);
	LuaBinder::pushLuaCFuncMethod(l, "getShadowEnabled", wrapLightComponentgetShadowEnabled);
	lua_settop(l, 0);
}

//==============================================================================
// LensFlareComponent                                                          =
//==============================================================================

//==============================================================================
static const char* classnameLensFlareComponent = "LensFlareComponent";

template<>
I64 LuaBinder::getWrappedTypeSignature<LensFlareComponent>()
{
	return -2019248835133422777;
}

template<>
const char* LuaBinder::getWrappedTypeName<LensFlareComponent>()
{
	return classnameLensFlareComponent;
}

//==============================================================================
/// Pre-wrap method LensFlareComponent::setFirstFlareSize.
static inline int pwrapLensFlareComponentsetFirstFlareSize(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLensFlareComponent, -2019248835133422777, ud)) return -1;
	LensFlareComponent* self = static_cast<LensFlareComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	if(LuaBinder::checkUserData(l, 2, "Vec2", 6804478823655046388, ud)) return -1;
	Vec2* iarg0 = static_cast<Vec2*>(ud->m_data);
	const Vec2& arg0(*iarg0);
	
	// Call the method
	self->setFirstFlareSize(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LensFlareComponent::setFirstFlareSize.
static int wrapLensFlareComponentsetFirstFlareSize(lua_State* l)
{
	int res = pwrapLensFlareComponentsetFirstFlareSize(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method LensFlareComponent::setColorMultiplier.
static inline int pwrapLensFlareComponentsetColorMultiplier(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameLensFlareComponent, -2019248835133422777, ud)) return -1;
	LensFlareComponent* self = static_cast<LensFlareComponent*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	if(LuaBinder::checkUserData(l, 2, "Vec4", 6804478823655046386, ud)) return -1;
	Vec4* iarg0 = static_cast<Vec4*>(ud->m_data);
	const Vec4& arg0(*iarg0);
	
	// Call the method
	self->setColorMultiplier(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method LensFlareComponent::setColorMultiplier.
static int wrapLensFlareComponentsetColorMultiplier(lua_State* l)
{
	int res = pwrapLensFlareComponentsetColorMultiplier(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class LensFlareComponent.
static inline void wrapLensFlareComponent(lua_State* l)
{
	LuaBinder::createClass(l, classnameLensFlareComponent);
	LuaBinder::pushLuaCFuncMethod(l, "setFirstFlareSize", wrapLensFlareComponentsetFirstFlareSize);
	LuaBinder::pushLuaCFuncMethod(l, "setColorMultiplier", wrapLensFlareComponentsetColorMultiplier);
	lua_settop(l, 0);
}

//==============================================================================
// SceneNode                                                                   =
//==============================================================================

//==============================================================================
static const char* classnameSceneNode = "SceneNode";

template<>
I64 LuaBinder::getWrappedTypeSignature<SceneNode>()
{
	return -2220074417980276571;
}

template<>
const char* LuaBinder::getWrappedTypeName<SceneNode>()
{
	return classnameSceneNode;
}

//==============================================================================
/// Pre-wrap method SceneNode::getName.
static inline int pwrapSceneNodegetName(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneNode, -2220074417980276571, ud)) return -1;
	SceneNode* self = static_cast<SceneNode*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	CString ret = self->getName();
	
	// Push return value
	lua_pushstring(l, &ret[0]);
	
	return 1;
}

//==============================================================================
/// Wrap method SceneNode::getName.
static int wrapSceneNodegetName(lua_State* l)
{
	int res = pwrapSceneNodegetName(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneNode::addChild.
static inline int pwrapSceneNodeaddChild(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneNode, -2220074417980276571, ud)) return -1;
	SceneNode* self = static_cast<SceneNode*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	if(LuaBinder::checkUserData(l, 2, "SceneNode", -2220074417980276571, ud)) return -1;
	SceneNode* iarg0 = static_cast<SceneNode*>(ud->m_data);
	SceneNode* arg0(iarg0);
	
	// Call the method
	self->addChild(arg0);
	
	return 0;
}

//==============================================================================
/// Wrap method SceneNode::addChild.
static int wrapSceneNodeaddChild(lua_State* l)
{
	int res = pwrapSceneNodeaddChild(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneNode::tryGetComponent<MoveComponent>.
static inline int pwrapSceneNodegetMoveComponent(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneNode, -2220074417980276571, ud)) return -1;
	SceneNode* self = static_cast<SceneNode*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	MoveComponent* ret = self->tryGetComponent<MoveComponent>();
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "MoveComponent");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = 2038493110845313445;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneNode::tryGetComponent<MoveComponent>.
static int wrapSceneNodegetMoveComponent(lua_State* l)
{
	int res = pwrapSceneNodegetMoveComponent(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneNode::tryGetComponent<LightComponent>.
static inline int pwrapSceneNodegetLightComponent(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneNode, -2220074417980276571, ud)) return -1;
	SceneNode* self = static_cast<SceneNode*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	LightComponent* ret = self->tryGetComponent<LightComponent>();
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "LightComponent");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = 7940823622056993903;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneNode::tryGetComponent<LightComponent>.
static int wrapSceneNodegetLightComponent(lua_State* l)
{
	int res = pwrapSceneNodegetLightComponent(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneNode::tryGetComponent<LensFlareComponent>.
static inline int pwrapSceneNodegetLensFlareComponent(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneNode, -2220074417980276571, ud)) return -1;
	SceneNode* self = static_cast<SceneNode*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	LensFlareComponent* ret = self->tryGetComponent<LensFlareComponent>();
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "LensFlareComponent");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = -2019248835133422777;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneNode::tryGetComponent<LensFlareComponent>.
static int wrapSceneNodegetLensFlareComponent(lua_State* l)
{
	int res = pwrapSceneNodegetLensFlareComponent(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class SceneNode.
static inline void wrapSceneNode(lua_State* l)
{
	LuaBinder::createClass(l, classnameSceneNode);
	LuaBinder::pushLuaCFuncMethod(l, "getName", wrapSceneNodegetName);
	LuaBinder::pushLuaCFuncMethod(l, "addChild", wrapSceneNodeaddChild);
	LuaBinder::pushLuaCFuncMethod(l, "getMoveComponent", wrapSceneNodegetMoveComponent);
	LuaBinder::pushLuaCFuncMethod(l, "getLightComponent", wrapSceneNodegetLightComponent);
	LuaBinder::pushLuaCFuncMethod(l, "getLensFlareComponent", wrapSceneNodegetLensFlareComponent);
	lua_settop(l, 0);
}

//==============================================================================
// ModelNode                                                                   =
//==============================================================================

//==============================================================================
static const char* classnameModelNode = "ModelNode";

template<>
I64 LuaBinder::getWrappedTypeSignature<ModelNode>()
{
	return -1856316251880904290;
}

template<>
const char* LuaBinder::getWrappedTypeName<ModelNode>()
{
	return classnameModelNode;
}

//==============================================================================
/// Pre-wrap method ModelNode::getSceneNodeBase.
static inline int pwrapModelNodegetSceneNodeBase(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameModelNode, -1856316251880904290, ud)) return -1;
	ModelNode* self = static_cast<ModelNode*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	SceneNode& ret = *self;
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneNode");
	ud->m_data = static_cast<void*>(&ret);
	ud->m_gc = false;
	ud->m_sig = -2220074417980276571;
	
	return 1;
}

//==============================================================================
/// Wrap method ModelNode::getSceneNodeBase.
static int wrapModelNodegetSceneNodeBase(lua_State* l)
{
	int res = pwrapModelNodegetSceneNodeBase(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class ModelNode.
static inline void wrapModelNode(lua_State* l)
{
	LuaBinder::createClass(l, classnameModelNode);
	LuaBinder::pushLuaCFuncMethod(l, "getSceneNodeBase", wrapModelNodegetSceneNodeBase);
	lua_settop(l, 0);
}

//==============================================================================
// InstanceNode                                                                =
//==============================================================================

//==============================================================================
static const char* classnameInstanceNode = "InstanceNode";

template<>
I64 LuaBinder::getWrappedTypeSignature<InstanceNode>()
{
	return -2063375830923741403;
}

template<>
const char* LuaBinder::getWrappedTypeName<InstanceNode>()
{
	return classnameInstanceNode;
}

//==============================================================================
/// Pre-wrap method InstanceNode::getSceneNodeBase.
static inline int pwrapInstanceNodegetSceneNodeBase(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameInstanceNode, -2063375830923741403, ud)) return -1;
	InstanceNode* self = static_cast<InstanceNode*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	SceneNode& ret = *self;
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneNode");
	ud->m_data = static_cast<void*>(&ret);
	ud->m_gc = false;
	ud->m_sig = -2220074417980276571;
	
	return 1;
}

//==============================================================================
/// Wrap method InstanceNode::getSceneNodeBase.
static int wrapInstanceNodegetSceneNodeBase(lua_State* l)
{
	int res = pwrapInstanceNodegetSceneNodeBase(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class InstanceNode.
static inline void wrapInstanceNode(lua_State* l)
{
	LuaBinder::createClass(l, classnameInstanceNode);
	LuaBinder::pushLuaCFuncMethod(l, "getSceneNodeBase", wrapInstanceNodegetSceneNodeBase);
	lua_settop(l, 0);
}

//==============================================================================
// PointLight                                                                  =
//==============================================================================

//==============================================================================
static const char* classnamePointLight = "PointLight";

template<>
I64 LuaBinder::getWrappedTypeSignature<PointLight>()
{
	return 3561037663389896020;
}

template<>
const char* LuaBinder::getWrappedTypeName<PointLight>()
{
	return classnamePointLight;
}

//==============================================================================
/// Pre-wrap method PointLight::getSceneNodeBase.
static inline int pwrapPointLightgetSceneNodeBase(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnamePointLight, 3561037663389896020, ud)) return -1;
	PointLight* self = static_cast<PointLight*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	SceneNode& ret = *self;
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneNode");
	ud->m_data = static_cast<void*>(&ret);
	ud->m_gc = false;
	ud->m_sig = -2220074417980276571;
	
	return 1;
}

//==============================================================================
/// Wrap method PointLight::getSceneNodeBase.
static int wrapPointLightgetSceneNodeBase(lua_State* l)
{
	int res = pwrapPointLightgetSceneNodeBase(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method PointLight::loadLensFlare.
static inline int pwrapPointLightloadLensFlare(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnamePointLight, 3561037663389896020, ud)) return -1;
	PointLight* self = static_cast<PointLight*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	// Call the method
	Error ret = self->loadLensFlare(arg0);
	
	// Push return value
	if(ANKI_UNLIKELY(ret))
	{
		lua_pushstring(l, "Glue code returned an error");
		return -1;
	}
	
	lua_pushnumber(l, ret);
	
	return 1;
}

//==============================================================================
/// Wrap method PointLight::loadLensFlare.
static int wrapPointLightloadLensFlare(lua_State* l)
{
	int res = pwrapPointLightloadLensFlare(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class PointLight.
static inline void wrapPointLight(lua_State* l)
{
	LuaBinder::createClass(l, classnamePointLight);
	LuaBinder::pushLuaCFuncMethod(l, "getSceneNodeBase", wrapPointLightgetSceneNodeBase);
	LuaBinder::pushLuaCFuncMethod(l, "loadLensFlare", wrapPointLightloadLensFlare);
	lua_settop(l, 0);
}

//==============================================================================
// SpotLight                                                                   =
//==============================================================================

//==============================================================================
static const char* classnameSpotLight = "SpotLight";

template<>
I64 LuaBinder::getWrappedTypeSignature<SpotLight>()
{
	return 7940385212889719421;
}

template<>
const char* LuaBinder::getWrappedTypeName<SpotLight>()
{
	return classnameSpotLight;
}

//==============================================================================
/// Pre-wrap method SpotLight::getSceneNodeBase.
static inline int pwrapSpotLightgetSceneNodeBase(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSpotLight, 7940385212889719421, ud)) return -1;
	SpotLight* self = static_cast<SpotLight*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	SceneNode& ret = *self;
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneNode");
	ud->m_data = static_cast<void*>(&ret);
	ud->m_gc = false;
	ud->m_sig = -2220074417980276571;
	
	return 1;
}

//==============================================================================
/// Wrap method SpotLight::getSceneNodeBase.
static int wrapSpotLightgetSceneNodeBase(lua_State* l)
{
	int res = pwrapSpotLightgetSceneNodeBase(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class SpotLight.
static inline void wrapSpotLight(lua_State* l)
{
	LuaBinder::createClass(l, classnameSpotLight);
	LuaBinder::pushLuaCFuncMethod(l, "getSceneNodeBase", wrapSpotLightgetSceneNodeBase);
	lua_settop(l, 0);
}

//==============================================================================
// StaticCollisionNode                                                         =
//==============================================================================

//==============================================================================
static const char* classnameStaticCollisionNode = "StaticCollisionNode";

template<>
I64 LuaBinder::getWrappedTypeSignature<StaticCollisionNode>()
{
	return -4376619865753613291;
}

template<>
const char* LuaBinder::getWrappedTypeName<StaticCollisionNode>()
{
	return classnameStaticCollisionNode;
}

//==============================================================================
/// Pre-wrap method StaticCollisionNode::getSceneNodeBase.
static inline int pwrapStaticCollisionNodegetSceneNodeBase(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameStaticCollisionNode, -4376619865753613291, ud)) return -1;
	StaticCollisionNode* self = static_cast<StaticCollisionNode*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	SceneNode& ret = *self;
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneNode");
	ud->m_data = static_cast<void*>(&ret);
	ud->m_gc = false;
	ud->m_sig = -2220074417980276571;
	
	return 1;
}

//==============================================================================
/// Wrap method StaticCollisionNode::getSceneNodeBase.
static int wrapStaticCollisionNodegetSceneNodeBase(lua_State* l)
{
	int res = pwrapStaticCollisionNodegetSceneNodeBase(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class StaticCollisionNode.
static inline void wrapStaticCollisionNode(lua_State* l)
{
	LuaBinder::createClass(l, classnameStaticCollisionNode);
	LuaBinder::pushLuaCFuncMethod(l, "getSceneNodeBase", wrapStaticCollisionNodegetSceneNodeBase);
	lua_settop(l, 0);
}

//==============================================================================
// Portal                                                                      =
//==============================================================================

//==============================================================================
static const char* classnamePortal = "Portal";

template<>
I64 LuaBinder::getWrappedTypeSignature<Portal>()
{
	return 7450426072538297652;
}

template<>
const char* LuaBinder::getWrappedTypeName<Portal>()
{
	return classnamePortal;
}

//==============================================================================
/// Pre-wrap method Portal::getSceneNodeBase.
static inline int pwrapPortalgetSceneNodeBase(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnamePortal, 7450426072538297652, ud)) return -1;
	Portal* self = static_cast<Portal*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	SceneNode& ret = *self;
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneNode");
	ud->m_data = static_cast<void*>(&ret);
	ud->m_gc = false;
	ud->m_sig = -2220074417980276571;
	
	return 1;
}

//==============================================================================
/// Wrap method Portal::getSceneNodeBase.
static int wrapPortalgetSceneNodeBase(lua_State* l)
{
	int res = pwrapPortalgetSceneNodeBase(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class Portal.
static inline void wrapPortal(lua_State* l)
{
	LuaBinder::createClass(l, classnamePortal);
	LuaBinder::pushLuaCFuncMethod(l, "getSceneNodeBase", wrapPortalgetSceneNodeBase);
	lua_settop(l, 0);
}

//==============================================================================
// Sector                                                                      =
//==============================================================================

//==============================================================================
static const char* classnameSector = "Sector";

template<>
I64 LuaBinder::getWrappedTypeSignature<Sector>()
{
	return 2371391302432627552;
}

template<>
const char* LuaBinder::getWrappedTypeName<Sector>()
{
	return classnameSector;
}

//==============================================================================
/// Pre-wrap method Sector::getSceneNodeBase.
static inline int pwrapSectorgetSceneNodeBase(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSector, 2371391302432627552, ud)) return -1;
	Sector* self = static_cast<Sector*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	SceneNode& ret = *self;
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneNode");
	ud->m_data = static_cast<void*>(&ret);
	ud->m_gc = false;
	ud->m_sig = -2220074417980276571;
	
	return 1;
}

//==============================================================================
/// Wrap method Sector::getSceneNodeBase.
static int wrapSectorgetSceneNodeBase(lua_State* l)
{
	int res = pwrapSectorgetSceneNodeBase(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class Sector.
static inline void wrapSector(lua_State* l)
{
	LuaBinder::createClass(l, classnameSector);
	LuaBinder::pushLuaCFuncMethod(l, "getSceneNodeBase", wrapSectorgetSceneNodeBase);
	lua_settop(l, 0);
}

//==============================================================================
// ParticleEmitter                                                             =
//==============================================================================

//==============================================================================
static const char* classnameParticleEmitter = "ParticleEmitter";

template<>
I64 LuaBinder::getWrappedTypeSignature<ParticleEmitter>()
{
	return -1716560948193631017;
}

template<>
const char* LuaBinder::getWrappedTypeName<ParticleEmitter>()
{
	return classnameParticleEmitter;
}

//==============================================================================
/// Pre-wrap method ParticleEmitter::getSceneNodeBase.
static inline int pwrapParticleEmittergetSceneNodeBase(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 1);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameParticleEmitter, -1716560948193631017, ud)) return -1;
	ParticleEmitter* self = static_cast<ParticleEmitter*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Call the method
	SceneNode& ret = *self;
	
	// Push return value
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneNode");
	ud->m_data = static_cast<void*>(&ret);
	ud->m_gc = false;
	ud->m_sig = -2220074417980276571;
	
	return 1;
}

//==============================================================================
/// Wrap method ParticleEmitter::getSceneNodeBase.
static int wrapParticleEmittergetSceneNodeBase(lua_State* l)
{
	int res = pwrapParticleEmittergetSceneNodeBase(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class ParticleEmitter.
static inline void wrapParticleEmitter(lua_State* l)
{
	LuaBinder::createClass(l, classnameParticleEmitter);
	LuaBinder::pushLuaCFuncMethod(l, "getSceneNodeBase", wrapParticleEmittergetSceneNodeBase);
	lua_settop(l, 0);
}

//==============================================================================
// SceneGraph                                                                  =
//==============================================================================

//==============================================================================
static const char* classnameSceneGraph = "SceneGraph";

template<>
I64 LuaBinder::getWrappedTypeSignature<SceneGraph>()
{
	return -7754439619132389154;
}

template<>
const char* LuaBinder::getWrappedTypeName<SceneGraph>()
{
	return classnameSceneGraph;
}

//==============================================================================
/// Pre-wrap method SceneGraph::newModelNode.
static inline int pwrapSceneGraphnewModelNode(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 3);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneGraph, -7754439619132389154, ud)) return -1;
	SceneGraph* self = static_cast<SceneGraph*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	const char* arg1;
	if(LuaBinder::checkString(l, 3, arg1)) return -1;
	
	// Call the method
	ModelNode* ret = newSceneNode<ModelNode>(self, arg0, arg1);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "ModelNode");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = -1856316251880904290;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneGraph::newModelNode.
static int wrapSceneGraphnewModelNode(lua_State* l)
{
	int res = pwrapSceneGraphnewModelNode(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneGraph::newInstanceNode.
static inline int pwrapSceneGraphnewInstanceNode(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneGraph, -7754439619132389154, ud)) return -1;
	SceneGraph* self = static_cast<SceneGraph*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	// Call the method
	InstanceNode* ret = newSceneNode<InstanceNode>(self, arg0);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "InstanceNode");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = -2063375830923741403;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneGraph::newInstanceNode.
static int wrapSceneGraphnewInstanceNode(lua_State* l)
{
	int res = pwrapSceneGraphnewInstanceNode(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneGraph::newPointLight.
static inline int pwrapSceneGraphnewPointLight(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneGraph, -7754439619132389154, ud)) return -1;
	SceneGraph* self = static_cast<SceneGraph*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	// Call the method
	PointLight* ret = newSceneNode<PointLight>(self, arg0);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "PointLight");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = 3561037663389896020;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneGraph::newPointLight.
static int wrapSceneGraphnewPointLight(lua_State* l)
{
	int res = pwrapSceneGraphnewPointLight(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneGraph::newSpotLight.
static inline int pwrapSceneGraphnewSpotLight(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 2);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneGraph, -7754439619132389154, ud)) return -1;
	SceneGraph* self = static_cast<SceneGraph*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	// Call the method
	SpotLight* ret = newSceneNode<SpotLight>(self, arg0);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SpotLight");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = 7940385212889719421;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneGraph::newSpotLight.
static int wrapSceneGraphnewSpotLight(lua_State* l)
{
	int res = pwrapSceneGraphnewSpotLight(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneGraph::newStaticCollisionNode.
static inline int pwrapSceneGraphnewStaticCollisionNode(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 4);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneGraph, -7754439619132389154, ud)) return -1;
	SceneGraph* self = static_cast<SceneGraph*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	const char* arg1;
	if(LuaBinder::checkString(l, 3, arg1)) return -1;
	
	if(LuaBinder::checkUserData(l, 4, "Transform", 7048620195620777229, ud)) return -1;
	Transform* iarg2 = static_cast<Transform*>(ud->m_data);
	const Transform& arg2(*iarg2);
	
	// Call the method
	StaticCollisionNode* ret = newSceneNode<StaticCollisionNode>(self, arg0, arg1, arg2);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "StaticCollisionNode");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = -4376619865753613291;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneGraph::newStaticCollisionNode.
static int wrapSceneGraphnewStaticCollisionNode(lua_State* l)
{
	int res = pwrapSceneGraphnewStaticCollisionNode(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneGraph::newPortal.
static inline int pwrapSceneGraphnewPortal(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 3);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneGraph, -7754439619132389154, ud)) return -1;
	SceneGraph* self = static_cast<SceneGraph*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	const char* arg1;
	if(LuaBinder::checkString(l, 3, arg1)) return -1;
	
	// Call the method
	Portal* ret = newSceneNode<Portal>(self, arg0, arg1);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "Portal");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = 7450426072538297652;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneGraph::newPortal.
static int wrapSceneGraphnewPortal(lua_State* l)
{
	int res = pwrapSceneGraphnewPortal(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneGraph::newSector.
static inline int pwrapSceneGraphnewSector(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 3);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneGraph, -7754439619132389154, ud)) return -1;
	SceneGraph* self = static_cast<SceneGraph*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	const char* arg1;
	if(LuaBinder::checkString(l, 3, arg1)) return -1;
	
	// Call the method
	Sector* ret = newSceneNode<Sector>(self, arg0, arg1);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "Sector");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = 2371391302432627552;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneGraph::newSector.
static int wrapSceneGraphnewSector(lua_State* l)
{
	int res = pwrapSceneGraphnewSector(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Pre-wrap method SceneGraph::newParticleEmitter.
static inline int pwrapSceneGraphnewParticleEmitter(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 3);
	
	// Get "this" as "self"
	if(LuaBinder::checkUserData(l, 1, classnameSceneGraph, -7754439619132389154, ud)) return -1;
	SceneGraph* self = static_cast<SceneGraph*>(ud->m_data);
	ANKI_ASSERT(self != nullptr);
	
	// Pop arguments
	const char* arg0;
	if(LuaBinder::checkString(l, 2, arg0)) return -1;
	
	const char* arg1;
	if(LuaBinder::checkString(l, 3, arg1)) return -1;
	
	// Call the method
	ParticleEmitter* ret = newSceneNode<ParticleEmitter>(self, arg0, arg1);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "ParticleEmitter");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = -1716560948193631017;
	
	return 1;
}

//==============================================================================
/// Wrap method SceneGraph::newParticleEmitter.
static int wrapSceneGraphnewParticleEmitter(lua_State* l)
{
	int res = pwrapSceneGraphnewParticleEmitter(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap class SceneGraph.
static inline void wrapSceneGraph(lua_State* l)
{
	LuaBinder::createClass(l, classnameSceneGraph);
	LuaBinder::pushLuaCFuncMethod(l, "newModelNode", wrapSceneGraphnewModelNode);
	LuaBinder::pushLuaCFuncMethod(l, "newInstanceNode", wrapSceneGraphnewInstanceNode);
	LuaBinder::pushLuaCFuncMethod(l, "newPointLight", wrapSceneGraphnewPointLight);
	LuaBinder::pushLuaCFuncMethod(l, "newSpotLight", wrapSceneGraphnewSpotLight);
	LuaBinder::pushLuaCFuncMethod(l, "newStaticCollisionNode", wrapSceneGraphnewStaticCollisionNode);
	LuaBinder::pushLuaCFuncMethod(l, "newPortal", wrapSceneGraphnewPortal);
	LuaBinder::pushLuaCFuncMethod(l, "newSector", wrapSceneGraphnewSector);
	LuaBinder::pushLuaCFuncMethod(l, "newParticleEmitter", wrapSceneGraphnewParticleEmitter);
	lua_settop(l, 0);
}

//==============================================================================
/// Pre-wrap function getSceneGraph.
static inline int pwrapgetSceneGraph(lua_State* l)
{
	UserData* ud;
	(void)ud;
	void* voidp;
	(void)voidp;
	
	LuaBinder::checkArgsCount(l, 0);
	
	// Call the function
	SceneGraph* ret = getSceneGraph(l);
	
	// Push return value
	if(ANKI_UNLIKELY(ret == nullptr))
	{
		lua_pushstring(l, "Glue code returned nullptr");
		return -1;
	}
	
	voidp = lua_newuserdata(l, sizeof(UserData));
	ud = static_cast<UserData*>(voidp);
	luaL_setmetatable(l, "SceneGraph");
	ud->m_data = static_cast<void*>(ret);
	ud->m_gc = false;
	ud->m_sig = -7754439619132389154;
	
	return 1;
}

//==============================================================================
/// Wrap function getSceneGraph.
static int wrapgetSceneGraph(lua_State* l)
{
	int res = pwrapgetSceneGraph(l);
	if(res >= 0) return res;
	lua_error(l);
	return 0;
}

//==============================================================================
/// Wrap the module.
void wrapModuleScene(lua_State* l)
{
	wrapMoveComponent(l);
	wrapLightComponent(l);
	wrapLensFlareComponent(l);
	wrapSceneNode(l);
	wrapModelNode(l);
	wrapInstanceNode(l);
	wrapPointLight(l);
	wrapSpotLight(l);
	wrapStaticCollisionNode(l);
	wrapPortal(l);
	wrapSector(l);
	wrapParticleEmitter(l);
	wrapSceneGraph(l);
	LuaBinder::pushLuaCFunc(l, "getSceneGraph", wrapgetSceneGraph);
}

} // end namespace anki

