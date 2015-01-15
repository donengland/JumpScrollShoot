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
	BulletComponent(Entity *e, float angle, float magnitude);

	void setEntity(Entity *bulletEntity);
	void receive(ComponentMessage message);
	void update(float deltaTime);
private:
	Entity *entity;
	float xVel, yVel;
};

#endif