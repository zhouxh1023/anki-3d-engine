// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_PHYSICS_PLAYER_CONTROLLER_H
#define ANKI_PHYSICS_PLAYER_CONTROLLER_H

#include "anki/physics/PhysicsObject.h"

namespace anki {

/// @addtogroup physics
/// @{

/// Initializer for PhysicsPlayerController.
struct PhysicsPlayerControllerInitializer
{
	F32 m_mass = 83.0;
	F32 m_innerRadius = 0.30;
	F32 m_outerRadius = 0.50;
	F32 m_height = 1.9;
	F32 m_stepHeight = 1.9 * 0.33;
	Vec4 m_position = Vec4(0.0);
};

/// A player controller that walks the world.
class PhysicsPlayerController final: public PhysicsObject
{
public:
	using Initializer = PhysicsPlayerControllerInitializer;

	PhysicsPlayerController(PhysicsWorld* world)
	:	PhysicsObject(Type::PLAYER_CONTROLLER, world)
	{}

	ANKI_USE_RESULT Error create(const Initializer& init);

	// Update the state machine
	void setVelocity(F32 forwardSpeed, F32 strafeSpeed, F32 jumpSpeed, 
		const Vec4& forwardDir)
	{
		m_forwardSpeed = forwardSpeed;
		m_strafeSpeed = strafeSpeed;
		m_jumpSpeed = jumpSpeed;
		m_forwardDir = forwardDir;
	}

	void moveToPosition(const Vec4& position);

	const Transform& getTransform(Bool& updated)
	{
		updated = m_updated;
		m_updated = false;
		return m_trf;
	}

	static Bool classof(const PhysicsObject& c)
	{
		return c.getType() == Type::PLAYER_CONTROLLER;
	}

	/// @privatesection
	/// @{

	/// Called by Newton thread to update the controller.
	static void postUpdateKernelCallback(
		NewtonWorld* const world, 
		void* const context, 
		int threadIndex);
	/// @}

private:
	Vec4 m_upDir;
	Vec4 m_frontDir;
	Vec4 m_groundPlane;
	Vec4 m_groundVelocity;
	F32 m_innerRadius;
	F32 m_outerRadius;
	F32 m_height;
	F32 m_stepHeight;
	F32 m_maxSlope;
	F32 m_sphereCastOrigin;
	F32 m_restrainingDistance;
	Bool8 m_isJumping;
	NewtonCollision* m_castingShape;
	NewtonCollision* m_supportShape;
	NewtonCollision* m_upperBodyShape;
	NewtonBody* m_body;

	// State
	F32 m_forwardSpeed = 0.0;
	F32 m_strafeSpeed = 0.0;
	F32 m_jumpSpeed = 0.0;
	Vec4 m_forwardDir = Vec4(0.0, 0.0, -1.0, 0.0);
	Vec4 m_gravity;

	// Motion state
	Bool8 m_updated = true;
	Transform m_trf = {Transform::getIdentity()};
	Mat4 m_prevTrf = {Mat4::getIdentity()};

	static constexpr F32 MIN_RESTRAINING_DISTANCE = 1.0e-2;
	static constexpr U DESCRETE_MOTION_STEPS = 8;
	static constexpr U MAX_CONTACTS = 32;
	static constexpr U MAX_INTERGRATION_STEPS = 8;
	static constexpr F32 CONTACT_SKIN_THICKNESS = 0.025;
	static constexpr U MAX_SOLVER_ITERATIONS = 16;

	void setClimbSlope(F32 ang)
	{
		ANKI_ASSERT(ang >= 0.0);
		m_maxSlope = cos(ang);
	}

	Vec4 calculateDesiredOmega(const Vec4& headingAngle, F32 dt) const;

	Vec4 calculateDesiredVelocity(F32 forwardSpeed, F32 strafeSpeed, 
		F32 verticalSpeed, const Vec4& gravity, F32 dt) const;

	void calculateVelocity(F32 dt);

	F32 calculateContactKinematics(const Vec4& veloc, 
		const NewtonWorldConvexCastReturnInfo* contactInfo) const;

	void updateGroundPlane(Mat4& matrix, const Mat4& castMatrix, 
		const Vec4& dst, int threadIndex);

	void postUpdate(F32 dt, int threadIndex);

	static void onTransformCallback(
		const NewtonBody* const body, 
		const dFloat* const matrix, 
		int threadIndex);

	void onTransform(Mat4 matrix);
};
/// @}

} // end namespace anki

#endif

