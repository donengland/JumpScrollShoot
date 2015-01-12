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

	xVel = 0.f;
	yVel = 0.f;

	xAccel = 0.f;
	yAccel = 0.f;
}

void PhysicsComponent::receive(ComponentMessage message)
{
	
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

void PhysicsComponent::jump(float deltaTime)
{
	if (collider->isGrounded())
	{
		PhysicsForce inputJump;
		inputJump.angle = 90.f;
		inputJump.duration = 0.1f;
		inputJump.magnitude = 300.f;
		inputJump.decay = 0.f;
		addForce(inputJump);
	}
	std::cout << "Told to jump with deltaTime: " << deltaTime << std::endl;
};

/*
* Updates physics given a deltaTime in milliseconds
*/
void PhysicsComponent::update(float deltaTime)
{
	if (deltaTime > 1)
	{
		std::cout << "DeltaTime of :" << deltaTime << std::endl;
	}

	if (1)
	{
		// Check to apply gravity
		if (gravity)
		{
			if (collider->isGrounded())
			{
				// Need the ground to stop acceleration due to gravity...
				if (yVel > 0)
				{
					yAccel = 0;
					yVel = 0;
				}
			}
			else
			{
				// TODO(don): universal coordinate system
				//yAccel += 98.f;
				yVel += 80.f;
				if (yVel > 800.f)
				{
					yVel = 800.f;
				}
			}
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
					//xAccel += forceX;
					xVel += forceX;// *deltaTime;
				}
				if (abs(forceY) > 0.1f)
				{
					//yAccel -= forceY;
					yVel -= forceY;// *deltaTime;
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
		//xVel += xAccel * deltaTime;
		//yVel += yAccel * deltaTime;

		transform->changeX(xVel * deltaTime);
		transform->changeY(yVel * deltaTime);
	}
	else
	{
		transform->changeY(0.98f * deltaTime);
	}
}
