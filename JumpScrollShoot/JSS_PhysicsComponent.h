//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_PHYSICS_COMPONENT_H_GUARD
#define __JSS_PHYSICS_COMPONENT_H_GUARD

typedef unsigned __int32 uint32;

#include "JSS_Entity.h"
#include "JSS_Component.h"
#include "JSS_ColliderComponent.h"

/*
 * PhysicsComponent handles object motion, motion changes occur via applyForce()
 *    After forces are applied, call update with deltaTime in milliseconds to 
 *    update the position.
*/
class PhysicsComponent : public Component
{
public:
	/*
	 * Process message from associated entity
	*/
	void receive(ComponentMessage message);

	/*
	* Applies a force in "newtons" | where a "newton" is kilogram * pixel per second squared
	* TODO(don): Consider converting distance into meters
	*/
	void applyForce(float forceX, float forceY);

	/*
	* Updates physics given a deltaTime in milliseconds
	*/
	void update(uint32 deltaTime);

	void resolveCollisions(ColliderComponent *c, int numberOfColliders);

	// TODO(don): add bounds checking for members with Max (velocity, acceleration)
	void setCollider(ColliderComponent *newCollider) { collider = newCollider; }

	float getXVel() { return xVel; }
	float setXVel(float xVelocity) { xVel = xVelocity; }

	float getYVel() { return yVel; }
	float setYVel(float yVelocity) { yVel = yVelocity; }

	float getXVelMax() { return xVelMax; }
	float setXVelMax(float xVelocityMax) { xVelMax = xVelocityMax; }

	float getYVelMax() { return yVelMax; }
	float setYVelMax(float yVelocityMax) { yVelMax = yVelocityMax; }

	float getXAccel() { return xAccel; }
	float setXAccel(float xAcceleration) { xAccel = xAcceleration; }

	float getYAccel() { return yAccel; }
	float setYAccel(float yAcceleration) { yAccel = yAcceleration; }

	float getXAccelMax() { return xAccelMax; }
	float setXAccelMax(float xAccelerationMax) { xAccelMax = xAccelerationMax; }

	float getYAccelMax() { return yAccelMax; }
	float setYAccelMax(float yAccelerationMax) { yAccelMax = yAccelerationMax; }

	float getMass() { return mass; }
	float setMass(float Mass) { mass = Mass; }

private:
	Entity *entity;
	ColliderComponent *collider;

	float xPos;
	float yPos;

	float xVel;
	float yVel;

	float xVelMax;
	float yVelMax;

	float xAccel;
	float yAccel;

	float xAccelMax;
	float yAccelMax;

	float mass;
};

#endif