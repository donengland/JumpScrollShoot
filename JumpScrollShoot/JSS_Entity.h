//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_ENTITY_H_GUARD
#define __JSS_ENTITY_H_GUARD

#include <vector>
#include <algorithm>

#include "JSS_Component.h"

// NOTE(don): Entity contains pointers to components that hold it's state.
class Entity
{
public:
	Entity();
	Entity(float X, float Y);

	void broadcast(ComponentMessage message);
	void addComponent(Component *c);
	std::vector<Component*> getComponents(Component *c);

	void setX(float X);
	void setY(float Y);

	float getX();
	float getY();

	void changeX(float deltaX);
	void changeY(float deltaY);

	void setInputId(int id);
	void setGraphicsId(int id);
	void setColliderId(int id);
	void setPhysicsId(int id);

	int getInputId(int id);
	int getGraphicsId(int id);
	int getColliderId(int id);
	int getPhysicsId(int id);

private:
	float x, y;
	int inputIndex;
	int graphicsIndex;
	int colliderIndex;
	int physicsIndex;
	std::vector<Component*> myComponents;
};

#endif