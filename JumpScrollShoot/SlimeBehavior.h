//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_SLIME_BEHAVIOR_H_GUARD
#define __JSS_SLIME_BEHAVIOR_H_GUARD

#include <math.h>
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

#include "JSS_Entity.h"
#include "JSS_Component.h"


class SlimeBehavior: public Component
{
public:
	SlimeBehavior();
	SlimeBehavior(Entity *entity, int id, float xVel = 0.f, float yVel = 0.f);

	void setEntity(Entity *entity);
	void receive(ComponentMessage message);
	void update(float deltaTime, float *playerXY, int numPlayers);
	void setId(int id);
  int getId();
  bool get_active();
  void set_active(bool active);
private:
	Entity *entity_;
  bool active_;
	int id_;
	float xVel_, yVel_;
	float jumpTimer_;
	float jumpRate_;
};

#endif