//============================================================================
// Name        : 
// Author      : Don England
// Version     : 
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "JSS_Entity.h"

Entity::Entity()
{
	x = 0.0f;
	y = 0.0f;
}

Entity::Entity(float X, float Y)
{
	x = X;
	y = Y;
}

void Entity::broadcast(ComponentMessage message)
{
	for (auto &i : myComponents)
	{
		i->receive(message);
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
/*
void Entity::removeComponent(Component *c)
{
	myComponents.erase(std::remove(myComponents.begin(),
								   myComponents.end(),
								   c),
					   myComponents.end());
};
*/
void Entity::setX(float X) { x = X; }
void Entity::setY(float Y) { y = Y; }

float Entity::getX() { return x; }
float Entity::getY() { return y; }

void Entity::changeX(float deltaX) { x += deltaX; }
void Entity::changeY(float deltaY) { y += deltaY; }

void Entity::setInputId(int id) { inputIndex = id; }
void Entity::setGraphicsId(int id) { graphicsIndex = id; }
void Entity::setColliderId(int id) { colliderIndex = id; }
void Entity::setPhysicsId(int id) { physicsIndex = id; }

int Entity::getInputId(int id) { return inputIndex; }
int Entity::getGraphicsId(int id) { return graphicsIndex; }
int Entity::getColliderId(int id) { return colliderIndex; }
int Entity::getPhysicsId(int id) { return physicsIndex; }