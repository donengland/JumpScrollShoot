//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_PHYSICS_COMPONENT_H_GUARD
#define __JSS_PHYSICS_COMPONENT_H_GUARD

#define MAX_PHYSICS_FORCES 10

#include <math.h>
#include "JSS_Entity.h"
#include "JSS_Component.h"
#include "JSS_ColliderComponent.h"

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

struct PhysicsForce
{
	// 
	bool active;

	// direction and magnitude of force
	float angle;

	float magnitude;

	// Duration of force in seconds
	float duration;

	// Amount to reduce magnitude per second
	float decay;
};

/*
 * PhysicsComponent applies forces to attached transform over time
*/
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	PhysicsComponent(Entity *physicsEntity, ColliderComponent *physicsCollider, float Mass = 1.f, bool Gravity = true);
	/*
	 * Process message from associated entity
	*/
	void receive(ComponentMessage message);

	/*
	* Applies a force in "newtons" | where a "newton" is kilogram * pixel per second squared
	* TODO(don): Consider converting distance into meters
	*/
	bool addForce(PhysicsForce force);

	/*
	* Updates physics given a deltaTime in seconds
	*/
	void update(float deltaTime);

	float getXVel();
	void setXVel(float xVelocity);

	float getYVel();
	void setYVel(float yVelocity);

	float getXAccel();
	void setXAccel(float xAcceleration);

	float getYAccel();
	void setYAccel(float yAcceleration);

	float getMass();
	void setMass(float Mass);

private:
	PhysicsForce activeForces[MAX_PHYSICS_FORCES];
	Entity *entity;
	ColliderComponent *collider;

	float xVel;
	float yVel;

	float xAccel;
	float yAccel;

	float mass;

	float jumpAmount;
	bool jumping;

	bool gravity;
};

#endif