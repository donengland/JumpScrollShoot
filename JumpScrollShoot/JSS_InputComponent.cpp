//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "JSS_InputComponent.h"

InputComponent::InputComponent(Entity *entity, int id, float speed, float fireRate)
{
	entity_ = entity;
  id_ = id;
  active_ = true;

	speed_ = speed;

	firing_ = 0.f;
	fireRate_ = fireRate;
	facingRight_ = true;
};

void InputComponent::setEntity(Entity *entity)
{
	entity_ = entity;
	entity_->setBehavior(this, id_);
}

void InputComponent::setId(int id)
{
	id_ = id;
	entity_->setBehaviorId(id_);
}
int InputComponent::getId() { return id_; }

bool InputComponent::get_active() { return active_; }
void InputComponent::set_active(bool active) { active_ = active; }

void InputComponent::receive(ComponentMessage message)
{

};

void InputComponent::update(float deltaTime, float *playerXY, int numPlayers)
{

};

void InputComponent::processInput(EntityInput input, float deltaTime)
{
	if (entity_)
	{
		float changeAmount = speed_ * deltaTime;

		// NOTE(don): If diagonal movement is allowed, don't allow speed bonus
		/*
		if ((input.right || input.left) && (input.up || input.down))
		{
			// Don't allow speed to increase when moving diagonally
			changeAmount *= 0.7071f;
		}
		*/
		if (input.right)
		{
			entity_->changeX(changeAmount);
			facingRight_ = true;
		}

		if (input.left)
		{
			entity_->changeX(-changeAmount);
			facingRight_ = false;
		}

		// TODO(don): should up be global coordinate up, not screen space?
		// NOTE(don): rendering cares about screen space
		if (input.up)
		{
			//entity->changeY(-changeAmount);
		}

		if (input.down)
		{
			//entity->changeY(+changeAmount);
		}

		if (input.shoot)
		{
			if (firing_ < 0.f)
			{
				printf("Shoot!\n");
				ComponentMessage msg;
				msg.type = MessageType::Instantiate;
				msg.key = MessageKey::Bullet;
				msg.x = entity_->getX();
				msg.y = entity_->getY();
				if (facingRight_)
				{
					msg.value = 0.f;
				}
				else
				{
					msg.value = 180.f;
				}
				entity_->broadcast(msg);
				firing_ = fireRate_;
			}
		}

		if (input.jump)
		{
			if (!jumping_)
			{
				printf("Jump!\n");
				ComponentMessage msg;
				msg.type = MessageType::Physics;
				msg.key = MessageKey::Jump;
				msg.value = 1000.f;
				entity_->broadcast(msg);
				jumping_ = true;
			}
		}
		else
		{
			jumping_ = false;
		}
		if (firing_ >= 0.f)
		{
			firing_ -= deltaTime;
		}
	}
};