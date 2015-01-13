//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <iostream>
#include "JSS_PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
	activeForces[MAX_PHYSICS_FORCES] = {};
	entity = nullptr;
	transform = nullptr;
	collider = nullptr;

	mass = 1.0f;

	jumpAmount = 0.f;

	gravity = false;

	xVel = 0.f;
	yVel = 0.f;

	xAccel = 0.f;
	yAccel = 0.f;
}
PhysicsComponent::PhysicsComponent(Entity *physicsEntity, TransformComponent *physicsTransform, ColliderComponent *physicsCollider, float Mass, bool Gravity)
{
	activeForces[MAX_PHYSICS_FORCES] = {};
	entity = physicsEntity;
	transform = physicsTransform;
	collider = physicsCollider;

	mass = Mass;

	gravity = Gravity;

	jumpAmount = 1000.0f;

	xVel = 0.f;
	yVel = 0.f;

	xAccel = 0.f;
	yAccel = 0.f;
}

void PhysicsComponent::receive(ComponentMessage message)
{
	if (message.type == MessageType::Physics)
	{
		switch (message.key)
		{
			case MessageKey::Jump:
			{
				if (collider->isGrounded())
				{
					jumpAmount = message.value;
					jumping = true;
				}
			}
		}
	}
};

// NOTE(don): possible problem with ticks on applying forces (on collision)
//    perhaps maintain some standard tick rate of every 2 seconds?
bool PhysicsComponent::addForce(PhysicsForce force)
{
	// TODO(don): handle adding forces when there is no room
	//    remove the shortest duration? Sort by duration in general?
	bool result = false;
	for (int index = 0; index < MAX_PHYSICS_FORCES; index++)
	{
		if (activeForces[index].duration <= 0.f)
		{
			activeForces[index] = force;
			result = true;
			break;
		}
	}

	return result;
}

/*
* Updates physics given a deltaTime in milliseconds
*/
void PhysicsComponent::update(float deltaTime)
{
	// Check to apply gravity
	if (gravity)
	{
		if (collider->isGrounded())
		{
			// Need the ground to stop acceleration due to gravity...
			if (yVel > 0.f)
			{
				yAccel = 0.f;
				yVel = 0.f;
			}

			if (xVel != 0.f)
			{
				xVel = 0.f;
			}
		}
		else
		{
			// TODO(don): universal coordinate system
			yAccel = 98.f;
			//yVel += 80.f;
			if (yVel > 800.f)
			{
				yVel = 800.f;
			}
		}
	}
	if (jumping)
	{
		jumping = false;
		yAccel -= jumpAmount;

		// NOTE(don): example jump input below
		/*
		PhysicsForce inputJump;
		inputJump.angle = 90.f;
		inputJump.duration = deltaTime;
		inputJump.magnitude = 1000.f;
		inputJump.decay = 0.f;
		addForce(inputJump);
		*/
	}

	// 
	for (int index = 0; index < MAX_PHYSICS_FORCES; index++)
	{
		if (activeForces[index].duration > 0.f)
		{
			// Apply accelerations due to this force
			float totalForce = (activeForces[index].magnitude / mass);
			// NOTE(don): Cos(angle) gives x component, Sin(angle) gives y component
			float forceX = (float)((Cos(activeForces[index].angle)) * totalForce);
			float forceY = (float)((Sin(activeForces[index].angle)) * totalForce);

			if (abs(forceX) > 0.1f)
			{
				xAccel += forceX;
				//xVel += forceX;// *deltaTime;
			}
			if (abs(forceY) > 0.1f)
			{
				// NOTE(don): using flipped coordinate on y
				yAccel -= forceY;
				//yVel -= forceY;// *deltaTime;
			}

			// Decay the magnitude
			activeForces[index].magnitude -= activeForces[index].decay * deltaTime;

			// Reduce duration
			activeForces[index].duration -= deltaTime;
		}
	}
	// Update velocities
	// Note(don): F = ma
	// velocity = integral of acceleration dt
	// v_i*t + (1/2)*a*t^2
	// v_f = v_i + at
	xVel += xAccel;// *deltaTime;
	yVel += yAccel;// *deltaTime;

	transform->changeX(xVel * deltaTime);
	transform->changeY(yVel * deltaTime); 
}

void PhysicsComponent::setTransform(TransformComponent *newTransform) { transform = newTransform; }

float PhysicsComponent::getXVel() { return xVel; }
void PhysicsComponent::setXVel(float xVelocity) { xVel = xVelocity; }

float PhysicsComponent::getYVel() { return yVel; }
void PhysicsComponent::setYVel(float yVelocity) { yVel = yVelocity; }

float PhysicsComponent::getXAccel() { return xAccel; }
void PhysicsComponent::setXAccel(float xAcceleration) { xAccel = xAcceleration; }

float PhysicsComponent::getYAccel() { return yAccel; }
void PhysicsComponent::setYAccel(float yAcceleration) { yAccel = yAcceleration; }

float PhysicsComponent::getMass() { return mass; }
void PhysicsComponent::setMass(float Mass) { mass = Mass; }