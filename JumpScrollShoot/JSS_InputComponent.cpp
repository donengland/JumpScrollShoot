//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "JSS_InputComponent.h"

void InputComponent::receive(ComponentMessage message)
{

};

void InputComponent::processInput(EntityInput input, __int32 deltaTime)
{
	if (transform)
	{
		float changeAmount = speed * deltaTime;
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
			transform->changeY(-changeAmount);
		}

		if (input.down)
		{
			transform->changeY(+changeAmount);
		}
	}
};