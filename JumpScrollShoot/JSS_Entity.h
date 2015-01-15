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

#include "JSS_IEntityManager.h"
#include "JSS_Component.h"

struct EntityIds
{
	int entity;
	int input;
	int graphics;
	int collider;
	int physics;
	int behavior;
};

// NOTE(don): Entity contains pointers to components that hold most of it's state.
class Entity
{
public:
	Entity();

	Entity(IEntityManager *m, float X, float Y);

	void broadcast(ComponentMessage message);
	void addComponent(Component *c);
	std::vector<Component*> getComponents(Component *c);
	void clearComponents();

	void setX(float X);
	void setY(float Y);

	float getX();
	float getY();

	void changeX(float deltaX);
	void changeY(float deltaY);

	void setId(int id);
	void setInputId(int id);
	void setGraphicsId(int id);
	void setColliderId(int id);
	void setPhysicsId(int id);
	void setBehaviorId(int id);

	int getId();
	int getInputId();
	int getGraphicsId();
	int getColliderId();
	int getPhysicsId();
	int getBehaviorId();

	EntityIds getIds();

private:
	IEntityManager *manager;
	float x, y;
	int myId;
	int inputIndex;
	int graphicsIndex;
	int colliderIndex;
	int physicsIndex;
	int behaviorIndex;
	// TODO(don): change to array?
	std::vector<Component*> myComponents;
};

#endif