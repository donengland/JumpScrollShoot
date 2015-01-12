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
	numGraphics = 0;

	worldSize = 640;

	camCenterX = 0;
	camCenterY = 0;
	camHalfWidth = 320;
	camHalfHeight = 240;
	
	init = false;
}

void JumpScrollShoot::CreateBlock(float x, float y, float w, float h, uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
	Entity block;
	entities[numEntities] = block;
	numEntities++;

	TransformComponent  transform(x, y);
	transformComponents[numTransforms] = transform;
	numTransforms++;

	ColliderComponent collider(&entities[numEntities - 1], &transformComponents[numTransforms - 1], 0.f, 0.f, w, h);
	colliderComponents[numColliders] = collider;
	numColliders++;

	GraphicsComponent graphics(&entities[numEntities - 1], &transformComponents[numTransforms - 1], red, green, blue, alpha, w, h);
	graphicsComponents[numGraphics] = graphics;
	numGraphics++;

	entities[numEntities - 1].addComponent(&transformComponents[numTransforms - 1]);
	entities[numEntities - 1].addComponent(&colliderComponents[numColliders - 1]);
	entities[numEntities - 1].addComponent(&graphicsComponents[numColliders - 1]);
}

void JumpScrollShoot::GameInit()
{
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
		ColliderComponent playerCollider(&entities[0], &transformComponents[0], 0.f, 0.f, 50.f, 50.f, ColliderCategory::player);
		colliderComponents[0] = playerCollider;
		numColliders++;

		// GraphicsComponent created and copied over element 0 player one
		GraphicsComponent playerGraphics(&entities[0], &transformComponents[0], 0x00, 0x00, 0xFF, 0xFF, 50.f, 50.f);
		graphicsComponents[0] = playerGraphics;
		numGraphics++;

		// Tell entity[0] player one about components
		entities[0].addComponent(&transformComponents[0]);
		entities[0].addComponent(&inputComponents[0]);
		entities[0].addComponent(&colliderComponents[0]);
		entities[0].addComponent(&graphicsComponents[0]);
	}

	// NOTE(don): world entity for initial colliderComponent tests
	// Create World Entity
	{
		Entity world;
		entities[1] = world;
		numEntities++;

		// NOTE(don): Test different world sizes
		worldSize = 1000;
		TransformComponent worldTransform(0.f, 0.f);
		transformComponents[1] = worldTransform;
		numTransforms++;

		// Add colliders on boundaries
		ColliderComponent worldLeftCollider(&entities[1], &transformComponents[1], (float)(-worldSize), 0.f, (float)(worldSize), (float)(worldSize));
		ColliderComponent worldRightCollider(&entities[1], &transformComponents[1], (float)(worldSize), 0.f, (float)(worldSize), (float)(worldSize));
		ColliderComponent worldTopCollider(&entities[1], &transformComponents[1], (float)(-worldSize), (float)(-worldSize), (float)((worldSize * 3)), (float)(worldSize));
		ColliderComponent worldBottomCollider(&entities[1], &transformComponents[1], (float)(-worldSize), (float)(worldSize), (float)((worldSize * 3)), (float)(worldSize));
		colliderComponents[1] = worldLeftCollider;
		colliderComponents[2] = worldRightCollider;
		colliderComponents[3] = worldTopCollider;
		colliderComponents[4] = worldBottomCollider;
		numColliders += 4;

		// Add Black Graphics Components for world edges
		GraphicsComponent worldLeftGraphics(&entities[1], &transformComponents[1], 0x00, 0x00, 0x00, 0xFF, (float)(worldSize), (float)(worldSize), (float)(-worldSize), 0.f);
		GraphicsComponent worldRightGraphics(&entities[1], &transformComponents[1], 0x00, 0x00, 0x00, 0xFF, (float)(worldSize), (float)(worldSize), (float)(worldSize), 0.f);
		GraphicsComponent worldTopGraphics(&entities[1], &transformComponents[1], 0x00, 0x00, 0x00, 0xFF, (float)((worldSize * 3)), (float)(worldSize), (float)(-worldSize), (float)(-worldSize));
		GraphicsComponent worldBottomGraphics(&entities[1], &transformComponents[1], 0x00, 0x00, 0x00, 0xFF, (float)((worldSize * 3)), (float)(worldSize), (float)(-worldSize), (float)(worldSize));
		graphicsComponents[1] = worldLeftGraphics;
		graphicsComponents[2] = worldRightGraphics;
		graphicsComponents[3] = worldTopGraphics;
		graphicsComponents[4] = worldBottomGraphics;
		numGraphics += 4;

		// Tell world about components
		entities[1].addComponent(&transformComponents[1]);
		entities[1].addComponent(&colliderComponents[1]);
		entities[1].addComponent(&colliderComponents[2]);
		entities[1].addComponent(&colliderComponents[3]);
		entities[1].addComponent(&colliderComponents[4]);
		entities[1].addComponent(&graphicsComponents[1]);
		entities[1].addComponent(&graphicsComponents[2]);
		entities[1].addComponent(&graphicsComponents[3]);
		entities[1].addComponent(&graphicsComponents[4]);
	}

	// create temp blocks
	{
		CreateBlock(600.f, 300.f, 100.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock(500.f, 400.f, 200.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock(400.f, 500.f, 300.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock(300.f, 600.f, 400.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock(0.f, 700.f, worldSize, 50.f, 0xFF, 0xFF, 0x00);
	}

	init = true;
}


void JumpScrollShoot::GameLoop(EntityInput* input, int NumInputs, uint32 deltaTime, SDL_Renderer *renderer)
{
	// TODO(don): look up branching rules.  Is it better to test init true?
	if (init == false)
	{
		GameInit();
		
		// TODO(don): Camera work
		camCenterX = 0;
		camCenterY = 0;
		camHalfWidth = 320;
		camHalfHeight = 240;
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
			ColliderCategory primaryCat = colliderComponents[primary].getCategory();

			// Reset previous collisions
			if (primaryCat != ColliderCategory::immobile)
			{
				colliderComponents[primary].resetCollisions();

				// Test for collisions with other colliderComponents
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
						colliderComponents[primary].resolveCollision(colliderComponents[secondary]);

						// TODO(don): Profiling - is it better to do double the checks in sequence or notify secondary immediately?
						ColliderCategory secondaryCat = colliderComponents[secondary].getCategory();
						if (secondaryCat != ColliderCategory::immobile)
						{
							// Notify other component of collision
							colliderComponents[secondary].resolveCollision(colliderComponents[primary]);
						}
					}
				}
			}
			if (primaryCat == ColliderCategory::player)
			{
				// TODO(don): keep players within camera borders?
			}
		}


		// Move camera over player
		// TODO(don): Use averaged player position for camera center point
		camCenterX = (int)transformComponents[0].getX();
		camCenterY = (int)transformComponents[0].getY();
		// TODO(don): Adjust camera if it goes past an edge
		// TODO(don): assert camera smaller than world
		if ((camCenterX - camHalfWidth) < 0)
		{
			camCenterX = camHalfWidth;
		}
		else if ((camCenterX + camHalfWidth) > worldSize)
		{
			camCenterX = worldSize - camHalfWidth;
		}
		if ((camCenterY - camHalfHeight) < 0)
		{
			camCenterY = camHalfHeight;
		}
		else if ((camCenterY + camHalfHeight) > worldSize)
		{
			camCenterY = worldSize - camHalfHeight;
		}


		// Process all rendering
		int xOffset = camCenterX - camHalfWidth;
		int yOffset = camCenterY - camHalfHeight;
		for (int index = 0; index < numGraphics; index++)
		{
			graphicsComponents[index].render(renderer, xOffset, yOffset);
		}
	}
}
