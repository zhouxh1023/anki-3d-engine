// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include "anki/collision/Frustum.h"
#include "anki/collision/LineSegment.h"
#include "anki/collision/Aabb.h"

namespace anki {

//==============================================================================
// Frustum                                                                     =
//==============================================================================

//==============================================================================
Frustum& Frustum::operator=(const Frustum& b)
{
	ANKI_ASSERT(m_type == b.m_type);
	m_near = b.m_near;
	m_far = b.m_far;
	m_planesL = b.m_planesL;
	m_planesW = b.m_planesW;
	m_trf = b.m_trf;
	m_frustumDirty = b.m_frustumDirty;
	return *this;
}

//==============================================================================
void Frustum::accept(MutableVisitor& v)
{
	update();
	CompoundShape::accept(v);
}

//==============================================================================
void Frustum::accept(ConstVisitor& v) const
{
	update();
	CompoundShape::accept(v);
}

//==============================================================================
F32 Frustum::testPlane(const Plane& p) const
{
	update();
	return CompoundShape::testPlane(p);
}

//==============================================================================
void Frustum::computeAabb(Aabb& aabb) const
{
	update();
	CompoundShape::computeAabb(aabb);
}

//==============================================================================
Bool Frustum::insideFrustum(const CollisionShape& b) const
{
	update();

	for(const Plane& plane : m_planesW)
	{
		if(b.testPlane(plane) < 0.0)
		{
			return false;
		}
	}

	return true;
}

//==============================================================================
void Frustum::transform(const Transform& trf)
{
	Transform trfa = m_trf.combineTransformations(trf);
	resetTransform(trfa);
}

//==============================================================================
void Frustum::resetTransform(const Transform& trf)
{
	m_trf = trf;

	if(m_frustumDirty)
	{
		// Update everything
		updateInternal();
	}
	else
	{
		// Inform the child about the change
		onTransform();

		// Transform the planes
		for(U i = 0; i < m_planesL.getSize(); ++i)
		{
			m_planesW[i] = m_planesL[i].getTransformed(m_trf);
		}
	}
}

//==============================================================================
void Frustum::update() const
{
	Frustum& self = *const_cast<Frustum*>(this);
	if(self.m_frustumDirty)
	{
		self.updateInternal();
	}
}

//==============================================================================
void Frustum::updateInternal()
{
	ANKI_ASSERT(m_frustumDirty);
	m_frustumDirty = false;	
	recalculate();

	// Transform derived
	onTransform();

	// Transform the planes
	for(U i = 0; i < m_planesL.getSize(); ++i)
	{
		m_planesW[i] = m_planesL[i].getTransformed(m_trf);
	}
}

//==============================================================================
// PerspectiveFrustum                                                          =
//==============================================================================

//==============================================================================
PerspectiveFrustum::PerspectiveFrustum()
:	Frustum(Type::PERSPECTIVE)
{
	addShape(&m_hull);
	m_hull.initStorage(&m_pointsW[0], m_pointsW.getSize());
}

//==============================================================================
PerspectiveFrustum& PerspectiveFrustum::operator=(const PerspectiveFrustum& b)
{
	Frustum::operator=(b);
	m_fovX = b.m_fovX;
	m_fovY = b.m_fovY;
	m_pointsL = b.m_pointsL;
	m_pointsW = b.m_pointsW;
	return *this;
}

//==============================================================================
void PerspectiveFrustum::onTransform()
{
	// Eye
	m_pointsW[0] = m_trf.getOrigin();

	for(U i = 1; i < 5; ++i)
	{
		m_pointsW[i] = m_trf.transform(m_pointsL[i - 1]);
	}
}

//==============================================================================
void PerspectiveFrustum::recalculate()
{
	// Planes
	//
	F32 c, s; // cos & sine

	sinCos(getPi<F32>() + m_fovX / 2.0, s, c);
	// right
	m_planesL[(U)PlaneType::RIGHT] = Plane(Vec4(c, 0.0, s, 0.0), 0.0);
	// left
	m_planesL[(U)PlaneType::LEFT] = Plane(Vec4(-c, 0.0, s, 0.0), 0.0);

	sinCos((getPi<F32>() + m_fovY) * 0.5, s, c);
	// bottom
	m_planesL[(U)PlaneType::BOTTOM] = Plane(Vec4(0.0, s, c, 0.0), 0.0);
	// top
	m_planesL[(U)PlaneType::TOP] = Plane(Vec4(0.0, -s, c, 0.0), 0.0);

	// near
	m_planesL[(U)PlaneType::NEAR] = Plane(Vec4(0.0, 0.0, -1.0, 0.0), m_near);
	// far
	m_planesL[(U)PlaneType::FAR] = Plane(Vec4(0.0, 0.0, 1.0, 0.0), -m_far);

	// Points
	//
	Vec4 eye = Vec4(0.0, 0.0, -m_near, 0.0);
	for(Vec4& p : m_pointsL)
	{
		p = eye;
	}

	F32 x = m_far / tan((getPi<F32>() - m_fovX) / 2.0);
	F32 y = tan(m_fovY / 2.0) * m_far;
	F32 z = -m_far;

	m_pointsL[0] += Vec4(x, y, z - m_near, 0.0); // top right
	m_pointsL[1] += Vec4(-x, y, z - m_near, 0.0); // top left
	m_pointsL[2] += Vec4(-x, -y, z - m_near, 0.0); // bot left
	m_pointsL[3] += Vec4(x, -y, z - m_near, 0.0); // bot right
}

//==============================================================================
Mat4 PerspectiveFrustum::calculateProjectionMatrix() const
{
	ANKI_ASSERT(m_fovX != 0.0 && m_fovY != 0.0 && m_near != 0.0);
	Mat4 projectionMat;
	F32 g = m_near - m_far;

#if 0
	projectionMat(0, 0) = 1.0 / tanf(m_fovX * 0.5);
	projectionMat(0, 1) = 0.0;
	projectionMat(0, 2) = 0.0;
	projectionMat(0, 3) = 0.0;
	projectionMat(1, 0) = 0.0;
	projectionMat(1, 1) = 1.0 / tanf(m_fovY * 0.5);
	projectionMat(1, 2) = 0.0;
	projectionMat(1, 3) = 0.0;
	projectionMat(2, 0) = 0.0;
	projectionMat(2, 1) = 0.0;
	projectionMat(2, 2) = (m_far + m_near) / g;
	projectionMat(2, 3) = (2.0 * m_far * m_near) / g;
	projectionMat(3, 0) = 0.0;
	projectionMat(3, 1) = 0.0;
	projectionMat(3, 2) = -1.0;
	projectionMat(3, 3) = 0.0;
#else
	float f = 1.0 / tan(m_fovY * 0.5); // f = cot(m_fovY/2)

	projectionMat(0, 0) = f * m_fovY / m_fovX; // = f/aspectRatio;
	projectionMat(0, 1) = 0.0;
	projectionMat(0, 2) = 0.0;
	projectionMat(0, 3) = 0.0;
	projectionMat(1, 0) = 0.0;
	projectionMat(1, 1) = f;
	projectionMat(1, 2) = 0.0;
	projectionMat(1, 3) = 0.0;
	projectionMat(2, 0) = 0.0;
	projectionMat(2, 1) = 0.0;
	projectionMat(2, 2) = (m_far + m_near) / g;
	projectionMat(2, 3) = (2.0 * m_far * m_near) / g;
	projectionMat(3, 0) = 0.0;
	projectionMat(3, 1) = 0.0;
	projectionMat(3, 2) = -1.0;
	projectionMat(3, 3) = 0.0;
#endif

	return projectionMat;
}

//==============================================================================
// OrthographicFrustum                                                         =
//==============================================================================

//==============================================================================
OrthographicFrustum::OrthographicFrustum()
:	Frustum(Type::ORTHOGRAPHIC)
{
	addShape(&m_obbW);
}

//==============================================================================
OrthographicFrustum& OrthographicFrustum::operator=(
	const OrthographicFrustum& b)
{
	Frustum::operator=(b);
	m_left = b.m_left;
	m_right = b.m_right;
	m_top = b.m_top;
	m_bottom = b.m_bottom;
	m_obbL = b.m_obbL;
	m_obbW = b.m_obbW;
	return *this;
}

//==============================================================================
Mat4 OrthographicFrustum::calculateProjectionMatrix() const
{
	ANKI_ASSERT(m_right != 0.0 && m_left != 0.0 && m_top != 0.0 
		&& m_bottom != 0.0 && m_near != 0.0 && m_far != 0.0);
	F32 difx = m_right - m_left;
	F32 dify = m_top - m_bottom;
	F32 difz = m_far - m_near;
	F32 tx = -(m_right + m_left) / difx;
	F32 ty = -(m_top + m_bottom) / dify;
	F32 tz = -(m_far + m_near) / difz;
	Mat4 m;

	m(0, 0) = 2.0 / difx;
	m(0, 1) = 0.0;
	m(0, 2) = 0.0;
	m(0, 3) = tx;
	m(1, 0) = 0.0;
	m(1, 1) = 2.0 / dify;
	m(1, 2) = 0.0;
	m(1, 3) = ty;
	m(2, 0) = 0.0;
	m(2, 1) = 0.0;
	m(2, 2) = -2.0 / difz;
	m(2, 3) = tz;
	m(3, 0) = 0.0;
	m(3, 1) = 0.0;
	m(3, 2) = 0.0;
	m(3, 3) = 1.0;

	return m;
}

//==============================================================================
void OrthographicFrustum::recalculate()
{
	// Planes
	m_planesL[(U)PlaneType::LEFT] = 
		Plane(Vec4(1.0, 0.0, 0.0, 0.0), m_left);
	m_planesL[(U)PlaneType::RIGHT] = 
		Plane(Vec4(-1.0, 0.0, 0.0, 0.0), -m_right);

	m_planesL[(U)PlaneType::NEAR] = 
		Plane(Vec4(0.0, 0.0, -1.0, 0.0), m_near);
	m_planesL[(U)PlaneType::FAR] = 
		Plane(Vec4(0.0, 0.0, 1.0, 0.0), -m_far);
	m_planesL[(U)PlaneType::TOP] = 
		Plane(Vec4(0.0, -1.0, 0.0, 0.0), -m_top);
	m_planesL[(U)PlaneType::BOTTOM] = 
		Plane(Vec4(0.0, 1.0, 0.0, 0.0), m_bottom);

	// OBB
	Vec4 c((m_right + m_left) * 0.5, 
		(m_top + m_bottom) * 0.5, 
		-(m_far + m_near) * 0.5,
		0.0);
	Vec4 e = Vec4(m_right, m_top, -m_far, 0.0) - c;
	m_obbL = Obb(c, Mat3x4::getIdentity(), e);
}

//==============================================================================
void OrthographicFrustum::onTransform()
{
	m_obbW = m_obbL.getTransformed(m_trf);
}

} // end namespace anki
