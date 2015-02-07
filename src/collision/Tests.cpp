// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include "anki/collision/Tests.h"
#include "anki/collision/Aabb.h"
#include "anki/collision/Sphere.h"
#include "anki/collision/CompoundShape.h"
#include "anki/collision/LineSegment.h"
#include "anki/collision/Plane.h"
#include "anki/collision/Obb.h"
#include "anki/collision/GjkEpa.h"
#include "anki/util/Rtti.h"

namespace anki {

//==============================================================================
// Misc                                                                        =
//==============================================================================

//==============================================================================
static Bool gjk(const CollisionShape& a, const CollisionShape& b)
{
	Gjk gjk;
	return gjk.intersect(
		dcast<const ConvexShape&>(a), dcast<const ConvexShape&>(b));
}

//==============================================================================
static Bool test(const Aabb& a, const Aabb& b)
{
	// if separated in x direction
	if(a.getMin().x() > b.getMax().x() || b.getMin().x() > a.getMax().x())
	{
		return false;
	}

	// if separated in y direction
	if(a.getMin().y() > b.getMax().y() || b.getMin().y() > a.getMax().y())
	{
		return false;
	}

	// if separated in z direction
	if(a.getMin().z() > b.getMax().z() || b.getMin().z() > a.getMax().z())
	{
		return false;
	}

	// no separation, must be intersecting
	return true;
}

//==============================================================================
Bool test(const Aabb& aabb, const LineSegment& ls)
{
	F32 maxS = MIN_F32;
	F32 minT = MAX_F32;

	// do tests against three sets of planes
	for(U i = 0; i < 3; ++i)
	{
		// segment is parallel to plane
		if(isZero(ls.getDirection()[i]))
		{
			// segment passes by box
			if(ls.getOrigin()[i] < aabb.getMin()[i] 
				|| ls.getOrigin()[i] > aabb.getMax()[i])
			{
				return false;
			}
		}
		else
		{
			// compute intersection parameters and sort
			F32 s = (aabb.getMin()[i] - ls.getOrigin()[i]) 
				/ ls.getDirection()[i];
			F32 t = (aabb.getMax()[i] - ls.getOrigin()[i]) 
				/ ls.getDirection()[i];
			if(s > t)
			{
				F32 temp = s;
				s = t;
				t = temp;
			}

			// adjust min and max values
			if(s > maxS)
			{
				maxS = s;
			}
			if(t < minT)
			{
				minT = t;
			}

			// check for intersection failure
			if(minT < 0.0 || maxS > 1.0 || maxS > minT)
			{
				return false;
			}
		}
	}

	// done, have intersection
	return true;
}

//==============================================================================
static Bool test(const Aabb& aabb, const Sphere& s)
{
	const Vec4& c = s.getCenter();

	// find the box's closest point to the sphere
	Vec4 cp(0.0); // Closest Point
	for(U i = 0; i < 3; i++)
	{
		// if the center is greater than the max then the closest
		// point is the max
		if(c[i] > aabb.getMax()[i])
		{
			cp[i] = aabb.getMax()[i];
		}
		else if(c[i] < aabb.getMin()[i]) // relative to the above
		{
			cp[i] = aabb.getMin()[i];
		}
		else
		{
			// the c lies between min and max
			cp[i] = c[i];
		}
	}

	F32 rsq = s.getRadius() * s.getRadius();

	// if the c lies totally inside the box then the sub is the zero,
	// this means that the length is also zero and thus its always smaller
	// than rsq
	Vec4 sub = c - cp;

	if(sub.getLengthSquared() <= rsq)
	{
		return true;
	}

	return false;
}

//==============================================================================
static Bool test(const LineSegment& ls, const Obb& obb)
{
	F32 maxS = MIN_F32;
	F32 minT = MAX_F32;

	// compute difference vector
	Vec4 diff = obb.getCenter() - ls.getOrigin();

	// for each axis do
	for(U i = 0; i < 3; ++i)
	{
		// get axis i
		Vec4 axis = obb.getRotation().getColumn(i).xyz0();

		// project relative vector onto axis
		F32 e = axis.dot(diff);
		F32 f = ls.getDirection().dot(axis);

		// ray is parallel to plane
		if(isZero(f))
		{
			// ray passes by box
			if(-e - obb.getExtend()[i] > 0.0 || -e + obb.getExtend()[i] > 0.0)
			{
				return false;
			}
			continue;
		}

		F32 s = (e - obb.getExtend()[i]) / f;
		F32 t = (e + obb.getExtend()[i]) / f;

		// fix order
		if(s > t)
		{
			F32 temp = s;
			s = t;
			t = temp;
		}

		// adjust min and max values
		if(s > maxS)
		{
			maxS = s;
		}
		if(t < minT)
		{
			minT = t;
		}

		// check for intersection failure
		if(minT < 0.0 || maxS > 1.0 || maxS > minT)
		{
			return false;
		}
	}

	// done, have intersection
	return true;
}

//==============================================================================
Bool test(const LineSegment& ls, const Sphere& s)
{
	const Vec4& v = ls.getDirection();
	Vec4 w0 = s.getCenter() - ls.getOrigin();
	F32 w0dv = w0.dot(v);
	F32 rsq = s.getRadius() * s.getRadius();

	if(w0dv < 0.0) // if the ang is >90
	{
		return w0.getLengthSquared() <= rsq;
	}

	Vec4 w1 = w0 - v; // aka center - P1, where P1 = seg.origin + seg.dir
	F32 w1dv = w1.dot(v);

	if(w1dv > 0.0) // if the ang is <90
	{
		return w1.getLengthSquared() <= rsq;
	}

	// the big parenthesis is the projection of w0 to v
	Vec4 tmp = w0 - (v * (w0.dot(v) / v.getLengthSquared()));
	return tmp.getLengthSquared() <= rsq;
}

//==============================================================================
static Bool test(const Sphere& a, const Sphere& b)
{
	F32 tmp = a.getRadius() + b.getRadius();
	return (a.getCenter() - b.getCenter()).getLengthSquared() <= tmp * tmp;
}

//==============================================================================
// Matrix                                                                      =
//==============================================================================

template<typename A, typename B>
static Bool t(const CollisionShape& a, const CollisionShape& b)
{
	return test(dcast<const A&>(a), dcast<const B&>(b));
}

template<typename A, typename B>
static Bool tr(const CollisionShape& a, const CollisionShape& b)
{
	return test(dcast<const B&>(b), dcast<const A&>(a));
}

/// Test plane.
template<typename A>
static Bool txp(const CollisionShape& a, const CollisionShape& b)
{
	return dcast<const A&>(a).testPlane(dcast<const Plane&>(b));
}

/// Test plane.
template<typename A>
static Bool tpx(const CollisionShape& a, const CollisionShape& b)
{
	return txp<A>(b, a);
}

/// Compound shape.
Bool tcx(const CollisionShape& a, const CollisionShape& b)
{
	Bool inside = true;
	const CompoundShape& c = dcast<const CompoundShape&>(a);

	// Use the error to stop the loop
	Error err = c.iterateShapes([&](const CollisionShape& cs)
	{
		if(!testCollisionShapes(cs, b))
		{
			inside = false;
			return ErrorCode::FUNCTION_FAILED;
		}

		return ErrorCode::NONE;
	});
	(void)err;

	return inside;
}

/// Compound shape.
Bool txc(const CollisionShape& a, const CollisionShape& b)
{
	return tcx(b, a);
}

using Callback = Bool(*)(const CollisionShape& a, const CollisionShape& b);

static const U COUNT = U(CollisionShape::Type::COUNT);

static const Callback matrix[COUNT][COUNT] = {
/*          AABB                  Comp  LS                      OBB                   PL                  S               */
/* AABB */ {t<Aabb, Aabb>,        tcx,  tr<LineSegment, Aabb>,  gjk,                  tpx<Aabb>,          tr<Sphere, Aabb>       },  
/* Comp */ {txc,                  tcx,  txc,                    txc,                  tpx<CompoundShape>, txc                    },  
/* LS   */ {t<Aabb, LineSegment>, tcx,  nullptr,                tr<Obb, LineSegment>, tpx<LineSegment>,   tr<Sphere, LineSegment>},
/* OBB  */ {gjk,                  tcx,  t<LineSegment, Obb>,    gjk,                  tpx<Obb>,           gjk                    },
/* PL   */ {txp<Aabb>,            tcx,  txp<LineSegment>,       txp<Obb>,             nullptr,            txp<Sphere>            },
/* S    */ {t<Aabb, Sphere>,      tcx,  t<LineSegment, Sphere>, gjk,                  tpx<Sphere>,        t<Sphere, Sphere>      }};

} // end namespace anki

