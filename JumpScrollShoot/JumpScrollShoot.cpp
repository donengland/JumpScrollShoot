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
	numColliders = 0;
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

			// TODO(don): Resolve width and height at a higher level
			// ColliderComponent created and copied over element 0 player one
			ColliderComponent playerCollider(&entities[0], &transformComponents[0], 0.0f, 0.0f, 50.0f, 50.0f, ColliderCategory::player);
			colliderComponents[0] = playerCollider;
			numColliders++;

			// Tell entity[0] player one about components
			entities[0].addComponent(&transformComponents[0]);
			entities[0].addComponent(&inputComponents[0]);
			entities[0].addComponent(&colliderComponents[0]);
		}

		// NOTE(don): world entity for initial colliderComponent tests
		// Create World Entity
		{
			Entity world;
			entities[1] = world;
			numEntities++;

			// NOTE(don): Test different world sizes
			float worldSize = 640;
			TransformComponent worldTransform(0.0f, 0.0f);
			transformComponents[1] = worldTransform;
			numTransforms++;

			// Add colliders on boundaries
			ColliderComponent worldLeftCollider(&entities[1], &transformComponents[1], -(worldSize + 0.1f), 0.0f, worldSize, worldSize);
			ColliderComponent worldRightCollider(&entities[1], &transformComponents[1], (worldSize + 0.1f), 0.0f, worldSize, worldSize);
			ColliderComponent worldTopCollider(&entities[1], &transformComponents[1], -worldSize, -(worldSize + 0.1f), (worldSize * 2.0f), worldSize);
			ColliderComponent worldBottomCollider(&entities[1], &transformComponents[1], -worldSize, (worldSize + 0.1f), (worldSize * 2.0f), worldSize);
			colliderComponents[1] = worldLeftCollider;
			colliderComponents[2] = worldRightCollider;
			colliderComponents[3] = worldTopCollider;
			colliderComponents[4] = worldBottomCollider;
			numColliders += 4;

			// Tell world about components
			entities[1].addComponent(&transformComponents[1]);
			entities[1].addComponent(&colliderComponents[1]);
			entities[1].addComponent(&colliderComponents[2]);
			entities[1].addComponent(&colliderComponents[3]);
			entities[1].addComponent(&colliderComponents[4]);
		}

		// create temp blocks
		{
			Entity block1, block2;
			entities[numEntities] = block1;
			numEntities++;
			entities[numEntities] = block2;
			numEntities++;

			// Transform component created and copied over element 0 player one
			TransformComponent block1Transform(300.0f, 300.0f);
			transformComponents[numTransforms] = block1Transform;
			numTransforms++;
			TransformComponent block2Transform(350.0f, 350.0f);
			transformComponents[numTransforms] = block2Transform;
			numTransforms++;

			// TODO(don): Resolve width and height at a higher level
			// ColliderComponent created and copied over element 0 player one
			ColliderComponent block1Collider(&entities[numEntities-2], &transformComponents[numTransforms-2], 0.0f, 0.0f, 50.0f, 50.0f);
			colliderComponents[numColliders] = block1Collider;
			numColliders++;
			ColliderComponent block2Collider(&entities[numEntities - 1], &transformComponents[numTransforms - 1], 0.0f, 0.0f, 50.0f, 50.0f);
			colliderComponents[numColliders] = block2Collider;
			numColliders++;

			// Tell entity[0] player one about components
			entities[numEntities - 2].addComponent(&transformComponents[numTransforms -2]);
			entities[numEntities - 2].addComponent(&colliderComponents[numColliders - 2]);
			entities[numEntities - 1].addComponent(&transformComponents[numTransforms - 1]);
			entities[numEntities - 1].addComponent(&colliderComponents[numColliders - 1]);
		}
	}
	else
	{
		// Process all inputs
		for (int index = 0; index < numInputs; index++)
		{
			inputComponents[index].processInput(input[0], deltaTime);
		}

		// TODO(don): Implement a broad stage pass to reduce the number of comparisons
		//    try binary space partitioning (bsp)
		// Process all colliders
		for (int primary = 0; primary < numColliders; primary++)
		{
			// Reset previous collisions
			if (colliderComponents[primary].getCategory() != ColliderCategory::immobile)
			{
				colliderComponents[primary].resetCollisions();

				// Test for collisions with colliderComponents
				for (int secondary = primary + 1; secondary < numColliders; secondary++)
				{
					// Collision test between primary and secondary
					if (colliderComponents[primary].getMaxX() < colliderComponents[secondary].getMinX() ||
						colliderComponents[primary].getMinX() > colliderComponents[secondary].getMaxX() ||
						colliderComponents[primary].getMaxY() < colliderComponents[secondary].getMinY() ||
						colliderComponents[primary].getMinY() > colliderComponents[secondary].getMaxY())
					{
						// no component collision
					}
					else
					{
						// TODO(don): Logging collisions
						// we have a component collision
						//std::cout << "Collider[" << primary << "] had collision with Collider[" << secondary << "]\n" << std::endl;
						colliderComponents[primary].resolveCollision(colliderComponents[secondary]);
					}
				}
			}
		}

		// Process all rendering
		// TODO(don): turn this into a graphics component render call
		for (int index = 0; index < numTransforms; index++)
		{
			// Render player quad
			SDL_Rect transformRect = { (int)transformComponents[index].getX(), (int)transformComponents[index].getY(), 50, 50 };
			if (index == 0)
			{
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
				SDL_RenderFillRect(renderer, &transformRect);
			}
			else if (index == 1)
			{
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
				SDL_RenderFillRect(renderer, &transformRect);
			}
		}
	}
}
