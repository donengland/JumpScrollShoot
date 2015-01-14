//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "JSS_InputComponent.h"

InputComponent::InputComponent(Entity *inputEntity, float Speed, float FireRate)
{
	entity = inputEntity;

	speed = Speed;

	firing = 0.f;
	fireRate = FireRate;
};

void InputComponent::receive(ComponentMessage message)
{

};

void InputComponent::processInput(EntityInput input, float deltaTime)
{
	if (entity)
	{
		float changeAmount = speed * deltaTime;

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
			entity->changeX(changeAmount);
		}

		if (input.left)
		{
			entity->changeX(-changeAmount);
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
			if (firing < 0.f)
			{
				printf("Shoot!\n");
				ComponentMessage msg;
				msg.type = MessageType::Instantiate;
				msg.key = MessageKey::Damage;
				msg.value = 1;
				entity->broadcast(msg);
				firing = fireRate;
			}
		}

		if (input.jump)
		{
			if (!jumping)
			{
				printf("Jump!\n");
				ComponentMessage msg;
				msg.type = MessageType::Physics;
				msg.key = MessageKey::Jump;
				msg.value = 1000.f;
				entity->broadcast(msg);
				jumping = true;
			}
		}
		else
		{
			jumping = false;
		}
		if (firing >= 0.f)
		{
			firing -= deltaTime;
		}
	}
};