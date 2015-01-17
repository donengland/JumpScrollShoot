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
	activeForces_[MAX_PHYSICS_FORCES] = {};
	entity_ = nullptr;
	collider_ = nullptr;
	id_ = -1;

	mass_ = 1.0f;

	jumpAmount_ = 0.f;

	gravity_ = true;

	xVel_ = 0.f;
	yVel_ = 0.f;

	xAccel_ = 0.f;
	yAccel_ = 0.f;
};

PhysicsComponent::PhysicsComponent(Entity *entity, ColliderComponent *collider, int id, float mass, bool gravity)
{
	activeForces_[MAX_PHYSICS_FORCES] = {};
	entity_ = entity;
	collider_ = collider;
	id_ = id;

	mass_ = mass;

	gravity_ = gravity;

	jumpAmount_ = 1000.0f;

	xVel_ = 0.f;
	yVel_ = 0.f;

	xAccel_ = 0.f;
	yAccel_ = 0.f;
};

void PhysicsComponent::setEntity(Entity *entity)
{
	entity_ = entity;
	entity_->setPhysics(this, id_);
};

void PhysicsComponent::setId(int id)
{
	id_ = id;
	entity_->setPhysicsId(id_);
}

void PhysicsComponent::setCollider(ColliderComponent *c)
{
	collider_ = c;
};

void PhysicsComponent::updateCollider()
{
	collider_ = (ColliderComponent*)(entity_->getCollider());
}

void PhysicsComponent::receive(ComponentMessage message)
{
	if (message.type == MessageType::Physics)
	{
		switch (message.key)
		{
			case MessageKey::Jump:
			{
				if (collider_->isGrounded())
				{
					jumpAmount_ = message.value;
					jumping_ = true;
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
		if (activeForces_[index].duration <= 0.f)
		{
			activeForces_[index] = force;
			result = true;
			break;
		}
	}

	return result;
};

/*
* Updates physics given a deltaTime in milliseconds
*/
void PhysicsComponent::update(float deltaTime, float *playerXY, int numPlayers)
{
	// Check to apply gravity
	if (gravity_)
	{
		if (collider_->isGrounded())
		{
			// NOTE(don): Need the ground to stop positive yvelocity
			if (yVel_ > 0.f)
			{
				yAccel_ = 0.f;
				yVel_ = 0.f;
			}

			if (xVel_ != 0.f)
			{
				xVel_ = 0.f;
			}
		}
		else
		{
			// TODO(don): universal coordinate system
			yAccel_ = 98.f;
			if (yVel_ > 800.f)
			{
				yVel_ = 800.f;
			}
		}
	}
	if (jumping_)
	{
		jumping_ = false;
		yAccel_ -= jumpAmount_;

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
		if (activeForces_[index].duration > 0.f)
		{
			// Apply accelerations due to this force
			float totalForce = (activeForces_[index].magnitude / mass_);
			// NOTE(don): Cos(angle) gives x component, Sin(angle) gives y component
			float forceX = (float)((Cos(activeForces_[index].angle)) * totalForce);
			float forceY = (float)((Sin(activeForces_[index].angle)) * totalForce);

			if (abs(forceX) > 0.1f)
			{
				xAccel_ += forceX;
			}
			if (abs(forceY) > 0.1f)
			{
				// NOTE(don): using flipped coordinate on y
				yAccel_ -= forceY;
			}

			// Decay the magnitude
			activeForces_[index].magnitude -= activeForces_[index].decay * deltaTime;

			// Reduce duration
			activeForces_[index].duration -= deltaTime;
		}
	}
	// Update velocities
	// Note(don): F = ma
	// velocity = integral of acceleration dt
	// v_i*t + (1/2)*a*t^2
	// v_f = v_i + at
	xVel_ += xAccel_;
	yVel_ += yAccel_;

	entity_->changeX(xVel_ * deltaTime);
	entity_->changeY(yVel_ * deltaTime); 
};

float PhysicsComponent::getXVel() { return xVel_; }
void PhysicsComponent::setXVel(float xVel) { xVel_ = xVel; }

float PhysicsComponent::getYVel() { return yVel_; }
void PhysicsComponent::setYVel(float yVel) { yVel_ = yVel; }

float PhysicsComponent::getXAccel() { return xAccel_; }
void PhysicsComponent::setXAccel(float xAccel) { xAccel_ = xAccel; }

float PhysicsComponent::getYAccel() { return yAccel_; }
void PhysicsComponent::setYAccel(float yAccel) { yAccel_ = yAccel; }

float PhysicsComponent::getMass() { return mass_; }
void PhysicsComponent::setMass(float mass) { mass_ = mass; }