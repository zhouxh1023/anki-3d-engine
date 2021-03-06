// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_SCENE_INSTANCE_NODE_H
#define ANKI_SCENE_INSTANCE_NODE_H

#include "anki/scene/SceneNode.h"

namespace anki {

/// @addtogroup scene
/// @{

/// Instance component. Dummy used only for idendification
class InstanceComponent: public SceneComponent
{
public:
	static Bool classof(const SceneComponent& c)
	{
		return c.getType() == Type::INSTANCE;
	}

	InstanceComponent(SceneNode* node)
	:	SceneComponent(Type::INSTANCE, node)
	{}
};

/// Instance scene node
class InstanceNode: public SceneNode,  public MoveComponent, 
	public InstanceComponent
{
public:
	InstanceNode(SceneGraph* scene)
	:	SceneNode(scene), 
		MoveComponent(this, MoveComponent::Flag::IGNORE_PARENT_TRANSFORM),
		InstanceComponent(this)
	{}

	ANKI_USE_RESULT Error create(const CString& name)
	{
		ANKI_CHECK(SceneNode::create(name));
		addComponent(static_cast<MoveComponent*>(this));
		addComponent(static_cast<InstanceComponent*>(this));

		return ErrorCode::NONE;
	}
};
/// @}

} // end namespace anki

#endif

