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

	Entity(IEntityManager *m, int id, float x, float y);

	void broadcast(ComponentMessage message);

	void setInput(Component *input, int id);
	void setGraphics(Component *graphics, int id);
	void setCollider(Component *collider, int id);
	void setPhysics(Component *physics, int id);
	void setBehavior(Component *behavior, int id);

	Component *getInput();
	Component *getGraphics();
	Component *getCollider();
	Component *getPhysics();
	Component *getBehavior();

	void updateComponentLink();

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
	IEntityManager *manager_;
	Component *input_;
	Component *graphics_;
	Component *collider_;
	Component *physics_;
	Component *behavior_;

	float x_, y_;
	int id_;

	int inputIndex_;
	int graphicsIndex_;
	int colliderIndex_;
	int physicsIndex_;
	int behaviorIndex_;
};

#endif