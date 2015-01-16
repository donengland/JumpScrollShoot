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
	manager = nullptr;
	x = 0.0f;
	y = 0.0f;

	myId = -1;
	inputIndex = -1;
	graphicsIndex = -1;
	colliderIndex = -1;
	physicsIndex = -1;
	behaviorIndex = -1;
}

Entity::Entity(IEntityManager *m, float X, float Y)
{
	manager = m;
	x = X;
	y = Y;

	myId = -1;
	inputIndex = -1;
	graphicsIndex = -1;
	colliderIndex = -1;
	physicsIndex = -1;
	behaviorIndex =-1;
}

void Entity::broadcast(ComponentMessage message)
{
	if (message.type == MessageType::Instantiate)
	{
		//std::cout << "Entity: component asked to broadcast instantiate!" << std::endl;
		manager->instantiate(message);
	}
	else if (message.type == MessageType::DeleteMe)
	{
		//std::cout << "Entity(" << myId << "): component asked for deletion!" << std::endl;
		manager->deleteEntity(myId);
	}
	else
	{
		for (auto &i : myComponents)
		{
			i->receive(message);
		}
	}
};

void Entity::addComponent(Component *c)
{
	myComponents.push_back(c);
};

std::vector<Component*>Entity::getComponents(Component *c)
{
	return myComponents;
}

void Entity::clearComponents()
{
	myComponents.clear();
};

void Entity::setX(float X) { x = X; }
void Entity::setY(float Y) { y = Y; }

float Entity::getX() { return x; }
float Entity::getY() { return y; }

void Entity::changeX(float deltaX) { x += deltaX; }
void Entity::changeY(float deltaY) { y += deltaY; }

void Entity::setId(int id) { myId = id; }
void Entity::setInputId(int id) { inputIndex = id; }
void Entity::setGraphicsId(int id) { graphicsIndex = id; }
void Entity::setColliderId(int id) { colliderIndex = id; }
void Entity::setPhysicsId(int id) { physicsIndex = id; }
void Entity::setBehaviorId(int id) { behaviorIndex = id; }

int Entity::getId() { return myId; }
int Entity::getInputId() { return inputIndex; }
int Entity::getGraphicsId() { return graphicsIndex; }
int Entity::getColliderId() { return colliderIndex; }
int Entity::getPhysicsId() { return physicsIndex; }
int Entity::getBehaviorId() { return behaviorIndex; }

EntityIds Entity::getIds()
{
	EntityIds ids;
	ids.entity = myId;
	ids.input = inputIndex;
	ids.graphics = graphicsIndex;
	ids.collider = colliderIndex;
	ids.physics = physicsIndex;
	ids.behavior = behaviorIndex;
	
	return ids;
};