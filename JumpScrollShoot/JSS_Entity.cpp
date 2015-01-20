//============================================================================
// Name        : 
// Author      : Don England
// Version     : 
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <iostream>
#include "JSS_Entity.h"

Entity::Entity()
{
  manager_ = nullptr;
  active_ = false;
	x_ = 0.0f;
	y_ = 0.0f;

	id_ = -1;
	inputIndex_ = -1;
	input_ = nullptr;

	graphicsIndex_ = -1;
	graphics_ = nullptr;

	colliderIndex_ = -1;
	collider_ = nullptr;

	physicsIndex_ = -1;
	physics_ = nullptr;

	behaviorIndex_ = -1;
	behavior_ = nullptr;
}

Entity::Entity(IEntityManager *m, int id, float x, float y)
{
  manager_ = m;
  active_ = true;
	x_ = x;
	y_ = y;

	id_ = id;
	inputIndex_ = -1;
	input_ = nullptr;

	graphicsIndex_ = -1;
	graphics_ = nullptr;

	colliderIndex_ = -1;
	collider_ = nullptr;

	physicsIndex_ = -1;
	physics_ = nullptr;

	behaviorIndex_ = -1;
	behavior_ = nullptr;
}

void Entity::set_active(bool active) { active_ = active; }
bool Entity::get_active() { return active_; }

void Entity::broadcast(ComponentMessage message)
{
	if (message.type == MessageType::Instantiate)
	{
		//std::cout << "Entity: component asked to broadcast instantiate!" << std::endl;
		manager_->instantiate(message);
	}
	else if (message.type == MessageType::DeleteMe)
	{
		//std::cout << "Entity(" << myId << "): component asked for deletion!" << std::endl;
		manager_->deleteEntity(id_);
	}
	else
	{
		if (input_ != nullptr) { input_->receive(message); }
		if (graphics_ != nullptr) { graphics_->receive(message); }
		if (collider_ != nullptr) { collider_->receive(message); }
		if (physics_ != nullptr) { physics_->receive(message); }
		if (behavior_ != nullptr) { behavior_->receive(message); }
	}
};

void Entity::updateComponentLink()
{
	if (input_ != nullptr) { input_->setEntity(this); }
	if (graphics_ != nullptr) { graphics_->setEntity(this); }
	if (collider_ != nullptr) { collider_->setEntity(this); }
	if (physics_ != nullptr) { physics_->setEntity(this); }
	if (behavior_ != nullptr) { behavior_->setEntity(this); }
}

void Entity::setInput(Component *input, int id)
{
	inputIndex_ = id;
	input_ = input;
}
void Entity::setGraphics(Component *graphics, int id)
{
	graphicsIndex_ = id;
	graphics_ = graphics;
}
void Entity::setCollider(Component *collider, int id)
{
	colliderIndex_ = id;
	collider_ = collider;
}
void Entity::setPhysics(Component *physics, int id)
{
	physicsIndex_ = id;
	physics_ = physics;
}
void Entity::setBehavior(Component *behavior, int id)
{
	behaviorIndex_ = id;
	behavior_ = behavior;
}
void Entity::setId(int id)
{
	id_ = id;
	updateComponentLink();
}
int Entity::getId() { return id_; }

int Entity::getInputId() { return inputIndex_; }
int Entity::getGraphicsId() { return graphicsIndex_; }
int Entity::getColliderId() { return colliderIndex_; }
int Entity::getPhysicsId() { return physicsIndex_; }
int Entity::getBehaviorId() { return behaviorIndex_; }

void Entity::setInputId(int id) { inputIndex_ = id; }
void Entity::setGraphicsId(int id) { graphicsIndex_ = id; }
void Entity::setColliderId(int id) { colliderIndex_ = id; }
void Entity::setPhysicsId(int id) { physicsIndex_ = id; }
void Entity::setBehaviorId(int id) { behaviorIndex_ = id; }

Component *Entity::getInput() { return input_; }
Component *Entity::getGraphics() { return graphics_; }
Component *Entity::getCollider() { return collider_; }
Component *Entity::getPhysics() { return physics_; }
Component *Entity::getBehavior() { return behavior_; }

void Entity::setX(float x) { x_ = x; }
void Entity::setY(float y) { y_ = y; }

float Entity::getX() { return x_; }
float Entity::getY() { return y_; }

void Entity::changeX(float deltaX) { x_ += deltaX; }
void Entity::changeY(float deltaY) { y_ += deltaY; }

EntityIds Entity::getIds()
{
	EntityIds ids;
	ids.entity = id_;
	ids.input = inputIndex_;
	ids.graphics = graphicsIndex_;
	ids.collider = colliderIndex_;
	ids.physics = physicsIndex_;
	ids.behavior = behaviorIndex_;
	
	return ids;
};