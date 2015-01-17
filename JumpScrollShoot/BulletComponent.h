//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_BULLET_COMPONENT_H_GUARD
#define __JSS_BULLET_COMPONENT_H_GUARD

#include <math.h>
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

#include "JSS_Entity.h"
#include "JSS_Component.h"


class BulletComponent : public Component
{
public:
	BulletComponent();
	BulletComponent(Entity *entity, int id, float angle, float magnitude);

	void setEntity(Entity *entity);
	void receive(ComponentMessage message);
	void update(float deltaTime, float *playerXY, int numPlayers);

	void setId(int id);
	int getId();

private:
	Entity *entity_;
	int id_;
	float xVel_, yVel_;
};

#endif