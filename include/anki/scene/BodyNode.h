// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_SCENE_BODY_NODE_H
#define ANKI_SCENE_BODY_NODE_H

#include "anki/scene/SceneNode.h"
#include "anki/resource/CollisionResource.h"

namespace anki {

/// @addtogroup scene
/// @{

/// Node that gets affected by physics.
class BodyNode: public SceneNode
{
public:
	BodyNode(SceneGraph* scene)
	:	SceneNode(scene)
	{}

	~BodyNode();

	ANKI_USE_RESULT Error create(
		const CString& name, const CString& resourceFname);

private:
	CollisionResourcePtr m_rsrc;
	PhysicsBodyPtr m_body;
};
/// @}

} // end namespace anki

#endif
