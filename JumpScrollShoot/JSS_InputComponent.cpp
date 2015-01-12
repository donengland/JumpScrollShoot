//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "JSS_InputComponent.h"

InputComponent::InputComponent(Entity *inputEntity, TransformComponent *inputTransform, PhysicsComponent *inputPhysics, float Speed)
{
	entity = inputEntity;
	transform = inputTransform;
	physics = inputPhysics;

	speed = Speed;
};

void InputComponent::receive(ComponentMessage message)
{

};

void InputComponent::processInput(EntityInput input, float deltaTime)
{
	if (transform)
	{
		float changeAmount = speed * deltaTime;
		if ((input.right || input.left) && (input.up || input.down))
		{
			// Don't allow speed to increase when moving diagonally
			changeAmount *= 0.7071f;
		}
		if (input.right)
		{
			transform->changeX(changeAmount);
		}

		if (input.left)
		{
			transform->changeX(-changeAmount);
		}

		// TODO(don): should up be global coordinate up, not screen space?
		// NOTE(don): rendering cares about screen space
		if (input.up)
		{
			//transform->changeY(-changeAmount);
		}

		if (input.down)
		{
			//transform->changeY(+changeAmount);
		}

		if (input.shoot)
		{
			printf("Shoot!\n");
		}

		if (input.jump)
		{
			physics->jump(deltaTime);
		}
	}
};