// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include "anki/scene/Light.h"
#include "anki/scene/LensFlareComponent.h"
#include "anki/scene/MoveComponent.h"
#include "anki/scene/SpatialComponent.h"
#include "anki/scene/FrustumComponent.h"

namespace anki {

//==============================================================================
// LightFeedbackComponent                                                      =
//==============================================================================

/// Feedback component.
class LightFeedbackComponent: public SceneComponent
{
public:
	LightFeedbackComponent(SceneNode* node)
		: SceneComponent(SceneComponent::Type::NONE, node)
	{}

	Error update(SceneNode& node, F32, F32, Bool& updated) override
	{
		updated = false;
		Light& lnode = static_cast<Light&>(node);

		MoveComponent& move = node.getComponent<MoveComponent>();
		if(move.getTimestamp() == node.getGlobalTimestamp())
		{
			// Move updated
			lnode.onMoveUpdate(move);
		}

		LightComponent& light = node.getComponent<LightComponent>();
		if(light.getTimestamp() == node.getGlobalTimestamp())
		{
			// Shape updated
			lnode.onShapeUpdate(light);
		}

		return ErrorCode::NONE;
	}
};

//==============================================================================
// Light                                                                       =
//==============================================================================

//==============================================================================
Light::Light(SceneGraph* scene)
	: SceneNode(scene)
{}

//==============================================================================
Light::~Light()
{}


//==============================================================================
Error Light::create(const CString& name,
	LightComponent::LightType type,
	CollisionShape* shape)
{
	ANKI_CHECK(SceneNode::create(name));

	SceneComponent* comp;

	// Move component
	comp = getSceneAllocator().newInstance<MoveComponent>(this);
	addComponent(comp, true);

	// Light component
	comp = getSceneAllocator().newInstance<LightComponent>(this, type);
	addComponent(comp, true);

	// Feedback component
	comp = getSceneAllocator().newInstance<LightFeedbackComponent>(this);
	addComponent(comp, true);

	// Spatial component
	comp = getSceneAllocator().newInstance<SpatialComponent>(this, shape);
	addComponent(comp, true);

	return ErrorCode::NONE;
}

//==============================================================================
Error Light::frameUpdate(F32 prevUpdateTime, F32 crntTime)
{
	// Update frustum comps shadow info
	const LightComponent& lc = getComponent<LightComponent>();
	Bool castsShadow = lc.getShadowEnabled();

	Error err = iterateComponentsOfType<FrustumComponent>(
		[&](FrustumComponent& frc) -> Error
	{
		if(castsShadow)
		{
			frc.setEnabledVisibilityTests(
				FrustumComponent::VisibilityTestFlag::TEST_SHADOW_CASTERS);
		}
		else
		{
			frc.setEnabledVisibilityTests(
				FrustumComponent::VisibilityTestFlag::TEST_NONE);
		}

		return ErrorCode::NONE;
	});
	(void) err;

	return ErrorCode::NONE;
}

//==============================================================================
void Light::onMoveUpdateCommon(MoveComponent& move)
{
	// Update the frustums
	Error err = iterateComponentsOfType<FrustumComponent>(
		[&](FrustumComponent& fr) -> Error
	{
		fr.markTransformForUpdate();
		fr.getFrustum().resetTransform(move.getWorldTransform());

		return ErrorCode::NONE;
	});

	(void)err;

	// Update the spatial
	SpatialComponent& sp = getComponent<SpatialComponent>();
	sp.markForUpdate();
	sp.setSpatialOrigin(move.getWorldTransform().getOrigin());

	// Update the lens flare
	LensFlareComponent* lf = tryGetComponent<LensFlareComponent>();
	if(lf)
	{
		lf->setWorldPosition(move.getWorldTransform().getOrigin());
	}
}

//==============================================================================
void Light::onShapeUpdateCommon(LightComponent& light)
{
	// Update the frustums
	Error err = iterateComponentsOfType<FrustumComponent>(
		[&](FrustumComponent& fr) -> Error
	{
		fr.markShapeForUpdate();
		return ErrorCode::NONE;
	});

	(void)err;

	// Mark the spatial for update
	SpatialComponent& sp = getComponent<SpatialComponent>();
	sp.markForUpdate();
}

//==============================================================================
Error Light::loadLensFlare(const CString& filename)
{
	ANKI_ASSERT(tryGetComponent<LensFlareComponent>() == nullptr);

	LensFlareComponent* flareComp =
		getSceneAllocator().newInstance<LensFlareComponent>(this);

	Error err = ErrorCode::NONE;
	if(err = flareComp->create(filename))
	{
		getSceneAllocator().deleteInstance(flareComp);
		return err;
	}

	addComponent(flareComp);
	flareComp->setAutomaticCleanup(true);

	return ErrorCode::NONE;
}

//==============================================================================
// PointLight                                                                  =
//==============================================================================

//==============================================================================
PointLight::PointLight(SceneGraph* scene)
	: Light(scene)
{}

//==============================================================================
Error PointLight::create(const CString& name)
{
	return Light::create(name, LightComponent::LightType::POINT, &m_sphereW);
}

//==============================================================================
void PointLight::onMoveUpdate(MoveComponent& move)
{
	onMoveUpdateCommon(move);
	m_sphereW.setCenter(move.getWorldTransform().getOrigin());
}

//==============================================================================
void PointLight::onShapeUpdate(LightComponent& light)
{
	onShapeUpdateCommon(light);
	m_sphereW.setRadius(light.getRadius());
}

//==============================================================================
Error PointLight::frameUpdate(F32 prevUpdateTime, F32 crntTime)
{
#if 0
	if(getShadowEnabled() && m_shadowData == nullptr)
	{
		m_shadowData = getSceneAllocator().newInstance<ShadowData>(this);
		if(m_shadowData == nullptr)
		{
			return ErrorCode::OUT_OF_MEMORY;
		}

		const F32 ang = toRad(90.0);
		F32 dist = m_sphereW.getRadius();

		for(U i = 0; i < 6; i++)
		{
			m_shadowData->m_frustums[i].setAll(ang, ang, 0.1, dist);
			m_shadowData->m_localTrfs[i] = Transform::getIdentity();
		}

		auto& trfs = m_shadowData->m_localTrfs;
		Vec3 axis = Vec3(0.0, 1.0, 0.0);
		trfs[1].setRotation(Mat3x4(Mat3(Axisang(ang, axis))));
		trfs[2].setRotation(Mat3x4(Mat3(Axisang(ang * 2.0, axis))));
		trfs[3].setRotation(Mat3x4(Mat3(Axisang(ang * 3.0, axis))));

		axis = Vec3(1.0, 0.0, 0.0);
		trfs[4].setRotation(Mat3x4(Mat3(Axisang(ang, axis))));
		trfs[5].setRotation(Mat3x4(Mat3(Axisang(-ang, axis))));
	}
#endif

	return ErrorCode::NONE;
}

//==============================================================================
// SpotLight                                                                   =
//==============================================================================

//==============================================================================
SpotLight::SpotLight(SceneGraph* scene)
	: Light(scene)
{}

//==============================================================================
Error SpotLight::create(const CString& name)
{
	ANKI_CHECK(Light::create(
		name, LightComponent::LightType::SPOT, &m_frustum));

	FrustumComponent* fr =
		getSceneAllocator().newInstance<FrustumComponent>(this, &m_frustum);
	fr->setEnabledVisibilityTests(
		FrustumComponent::VisibilityTestFlag::TEST_NONE);

	addComponent(fr, true);

	return ErrorCode::NONE;
}

//==============================================================================
void SpotLight::onMoveUpdate(MoveComponent& move)
{
	onMoveUpdateCommon(move);
}

//==============================================================================
void SpotLight::onShapeUpdate(LightComponent& light)
{
	onShapeUpdateCommon(light);
	m_frustum.setAll(
		light.getOuterAngle(), light.getOuterAngle(),
		0.5, light.getDistance());
}

} // end namespace anki
