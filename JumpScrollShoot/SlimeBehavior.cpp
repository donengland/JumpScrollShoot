//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "SlimeBehavior.h"

SlimeBehavior::SlimeBehavior()
{
	entity_ = nullptr;
	id_ = -1;
	xVel_ = 0.f;
	yVel_ = 0.f;

	jumpTimer_ = 0.f;
	jumpRate_ = 3.f;
};

SlimeBehavior::SlimeBehavior(Entity *entity, int id, float xVel, float yVel)
{
	entity_ = entity;
	id_ = id;
	//entity_->setBehaviorId(id);
	xVel_ = xVel;
	yVel_ = yVel;

	jumpRate_ = 3.f;
	jumpTimer_ = jumpRate_;
}

void SlimeBehavior::setEntity(Entity *entity)
{
	entity_ = entity;
	entity_->setBehavior(this, id_);
};

void SlimeBehavior::setId(int id)
{
	id_ = id;
}
int SlimeBehavior::getId() { return id_; }

void SlimeBehavior::receive(ComponentMessage message)
{

};

void SlimeBehavior::update(float deltaTime, float *playerXY, int numPlayers)
{
	
	if (numPlayers == 1)
	{
		if (jumpTimer_ <= 0.f)
		{
			/*
			printf("Slime Jump!\n");
			ComponentMessage msg;
			msg.type = MessageType::Physics;
			msg.key = MessageKey::Jump;
			msg.value = 1000.f;
			entity->broadcast(msg);
			*/
			// Jump in place for now
			yVel_ -= 1200.f;
			if (playerXY[0] < entity_->getX())
			{
				// Jump left
				xVel_ -= 200.f;
			}
			else
			{
				// Jump right
				xVel_ += 200.f;
			}
			// Reset jumping time
			jumpTimer_ = jumpRate_;
		}
		else
		{
			jumpTimer_ -= deltaTime;
		}
	}

	if (yVel_ > 50.f)
	{
		yVel_ -= 50.f;
	}
	else if (yVel_ < -50.f)
	{
		yVel_ += 50.f;
	}
	else
	{
		xVel_ = 0.f;
		yVel_ = 0.f;
	}
	/*
	if (yVel < 300)
	{
		yVel += 98.f;
	}
	*/
	entity_->changeX(xVel_ * deltaTime);
	entity_->changeY(yVel_ * deltaTime);
};