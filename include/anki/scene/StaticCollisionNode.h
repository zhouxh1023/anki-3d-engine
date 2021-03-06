// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_SCENE_STATIC_COLLISION_H
#define ANKI_SCENE_STATIC_COLLISION_H

#include "anki/scene/SceneNode.h"
#include "anki/resource/Forward.h"
#include "anki/physics/Forward.h"

namespace anki {

/// @addtogroup scene
/// @{

/// Node that interacts with physics.
class StaticCollisionNode: public SceneNode
{
public:
	StaticCollisionNode(SceneGraph* scene)
	:	SceneNode(scene)
	{}

	~StaticCollisionNode();

	ANKI_USE_RESULT Error create(const CString& name,
		const CString& resourceFname, const Transform& transform);

private:
	CollisionResourcePtr m_rsrc;
	PhysicsBodyPtr m_body;
};
/// @}

} // end namespace anki

#endif

