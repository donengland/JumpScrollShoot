//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "JumpScrollShoot.h"

JumpScrollShoot::JumpScrollShoot()
{
	numEntities = 0;
	numTransforms = 0;
	numInputs = 0;
}


void JumpScrollShoot::GameLoop(EntityInput* input, int NumInputs, uint32 deltaTime, SDL_Renderer *renderer)
{
	static bool Init = false;
	if (Init == false)
	{
		Init = true;

		// Create player entity
		{
			// TODO(don): reserve first 4 entities for players?
			Entity player;
			entities[0] = player;
			numEntities++;

			// Transform component created and copied over element 0 player one
			TransformComponent playerTransform(100, 50);
			transformComponents[0] = playerTransform;
			numTransforms++;

			// InputComponent created and copied over element 0 player one
			InputComponent playerInput(&transformComponents[0], 0.5f);
			inputComponents[0] = playerInput;
			numInputs++;

			// Tell entity[0] player one about components
			entities[0].addComponent(&transformComponents[0]);
			entities[0].addComponent(&inputComponents[0]);
		}
	}
	else
	{
		// Process all inputs
		for (int index = 0; index < numInputs; index++)
		{
			inputComponents[index].processInput(input[0], deltaTime);
		}

		// Process all colliders

		// Process all rendering
		// TODO(don): turn this into a graphics component render call
		for (int index = 0; index < numTransforms; index++)
		{
			// Render player quad
			SDL_Rect transformRect = { (int)transformComponents[index].getX(), (int)transformComponents[index].getY(), 50, 50 };
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &transformRect);
		}
	}


	static float x = 100;
	static float y = 0;
	int w = 50;
	int h = 50;

	float speed = 0.5f;
	if (input[0].right)
	{
		x += speed * deltaTime;
		int maxX = 640 - w;
		if (x > maxX)
		{
			x = (float)maxX;
		}
	}

	if (input[0].left)
	{
		x -= speed * deltaTime;
		if (x < 0.0f)
		{
			x = 0.0f;
		}
	}

	if (input[0].up)
	{
		y -= speed * deltaTime;
		if (y < 0.0f)
		{
			y = 0.0f;
		}
	}

	if (input[0].down)
	{
		y += speed * deltaTime;
		int maxY = 480 - w;
		if (y > maxY)
		{
			y = (float)maxY;
		}
	}

	// Render player quad
	SDL_Rect playerRect = { (int)x, (int)y, w, h };
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &playerRect);
}
