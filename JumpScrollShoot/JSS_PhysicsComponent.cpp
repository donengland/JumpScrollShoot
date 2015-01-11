//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "JSS_PhysicsComponent.h"

void PhysicsComponent::receive(ComponentMessage message)
{
	
};

void PhysicsComponent::applyForce(float forceX, float forceY)
{
	xAccel += forceX / mass;
	yAccel += forceY / mass;

	// TODO(don): Would normalization work better? -1 to 1 | where 1 is maxAccel
	// Check for x acceleration bounds
	if (xAccel > xAccelMax)
	{
		xAccel = xAccelMax;
	}
	else if (xAccel < -xAccelMax)
	{
		xAccel = -xAccelMax;
	}

	// Check for y acceleration bounds
	if (yAccel > yAccelMax)
	{
		yAccel = yAccelMax;
	}
	else if (yAccel < -yAccelMax)
	{
		yAccel = -yAccelMax;
	}
}
/*
* Updates physics given a deltaTime in milliseconds
*/

void PhysicsComponent::update(uint32 deltaTime)
{
	// deltaTime is given in milliseconds, convert to seconds
	deltaTime = deltaTime / 1000;

	// Update velocities
	// Note(don): velocity = integral of acceleration dt
	// v_i*t + (1/2)*a*t^2
	// v_f = v_i + at
	xVel += xAccel * deltaTime;
	yVel += yAccel * deltaTime;

	// Bounds check x velocity
	if (xVel > xVelMax)
	{
		xVel = xVelMax;
	}
	else if (xVel < -xVelMax)
	{
		xVel = -xVelMax;
	}

	// Bounds check y Velcity
	if (yVel > yVelMax)
	{
		yVel = yVelMax;
	}
	else if (yVel < -yVelMax)
	{
		yVel = -yVelMax;
	}

	// TODO(don): Update Position
	xPos += xVel * deltaTime;
	yPos += yVel * deltaTime;
}

void PhysicsComponent::resolveCollisions(ColliderComponent *c, int numberOfColliders)
{
	for (int index = 0; index < numberOfColliders; index++)
	{
		// Valid collision
		// TODO(don): make damage team dependant
		// NOTE(don): What actions do I need to take here?
		//	(1) Adjust position based on collisions with solids
		//	(2) Adjust position to move with mobile platform
		//		(2.a) Need to know mobile platforms velocity...
		//  (3) Tell owner about collision with opponent/opponentAttack
		switch (c[index].getCategory())
		{
			case ColliderCategory::enemy: // Fall Through
			case ColliderCategory::enemyAttack:
			{
				if (collider->getCategory() == ColliderCategory::player)
				{
					// TODO(don): take damage
				}
			} break;
			case ColliderCategory::immobile:
			{
				// TODO(don): change position back
			} break;
			case ColliderCategory::mobile:
			{
				// TODO(don): change position back, and move with collider?
			} break;
			case ColliderCategory::player: // Fall Through
			case ColliderCategory::playerAttack:
			{
				if (collider->getCategory() == ColliderCategory::enemy)
				{
					// TODO(don): take damage
				}
			} break;
		}
	}

	// process all contact points
}