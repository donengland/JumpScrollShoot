//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <iostream>
#include "EntityManager.h"

EntityManager::EntityManager()
{
	numEntities = 0;
	numInputs = 0;
	numColliders = 0;
	numGraphics = 0;
	numPhysics = 0;

	// TODO(don): Camera work
	camCenterX = 0;
	camCenterY = 0;
	camHalfWidth = 320;
	camHalfHeight = 240;
	camSpeed = 15.f;
}

void EntityManager::CreateBlock(float x, float y, float w, float h, uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
	Entity block(this, x, y);
	entities[numEntities] = block;
	numEntities++;

	ColliderComponent collider(&entities[numEntities - 1], 0.f, 0.f, w, h);
	colliderComponents[numColliders] = collider;
	numColliders++;

	GraphicsComponent graphics(&entities[numEntities - 1], red, green, blue, alpha, w, h);
	graphicsComponents[numGraphics] = graphics;
	numGraphics++;

	entities[numEntities - 1].addComponent(&colliderComponents[numColliders - 1]);
	entities[numEntities - 1].addComponent(&graphicsComponents[numColliders - 1]);
}

bool EntityManager::loadWorld()
{
	bool result = false;

	// TODO(don): Load world from file/database/etc

	// Create player entity
	{
		// TODO(don): reserve first 4 entities for players?
		Entity player(this, 100.f, 300.f);
		entities[0] = player;
		numEntities++;

		// TODO(don): Resolve width and height at a higher level
		// ColliderComponent created and copied over element 0 player one
		ColliderComponent playerCollider(&entities[0], 0.f, 0.f, 50.f, 50.f, ColliderCategory::player);
		colliderComponents[0] = playerCollider;
		numColliders++;

		// GraphicsComponent created and copied over element 0 player one
		GraphicsComponent playerGraphics(&entities[0], 0x00, 0x00, 0xFF, 0xFF, 50.f, 50.f);
		graphicsComponents[0] = playerGraphics;
		numGraphics++;

		// PhysicsComponent created and copied over element 0 player one
		PhysicsComponent playerPhysics(&entities[0], &colliderComponents[0]);
		physicsComponents[0] = playerPhysics;
		numPhysics++;

		// InputComponent created and copied over element 0 player one
		InputComponent playerInput(&entities[0], 300.f, 0.25f);
		inputComponents[0] = playerInput;
		numInputs++;

		// Tell entity[0] player one about components
		entities[0].addComponent(&inputComponents[0]);
		entities[0].addComponent(&colliderComponents[0]);
		entities[0].addComponent(&graphicsComponents[0]);
		entities[0].addComponent(&physicsComponents[0]);
	}

	// TODO(don): world needs edge bounds only, camera can restrict movement from there
	//    Perhaps a secondary grid for camera restrictions?
	// NOTE(don): world entity for initial colliderComponent tests
	// Create World Entity
	{
		Entity world(this, 0.f, 0.f);
		entities[1] = world;
		numEntities++;

		// NOTE(don): Test different world sizes
		worldSize = 1000;

		// Add colliders on boundaries
		ColliderComponent worldLeftCollider(&entities[1], (float)(-worldSize), 0.f, (float)(worldSize), (float)(worldSize));
		ColliderComponent worldRightCollider(&entities[1], (float)(worldSize), 0.f, (float)(worldSize), (float)(worldSize));
		ColliderComponent worldTopCollider(&entities[1], (float)(-worldSize), (float)(-worldSize), (float)((worldSize * 3)), (float)(worldSize));
		ColliderComponent worldBottomCollider(&entities[1], (float)(-worldSize), (float)(worldSize), (float)((worldSize * 3)), (float)(worldSize));
		colliderComponents[1] = worldLeftCollider;
		colliderComponents[2] = worldRightCollider;
		colliderComponents[3] = worldTopCollider;
		colliderComponents[4] = worldBottomCollider;
		numColliders += 4;

		// Add Black Graphics Components for world edges
		GraphicsComponent worldLeftGraphics(&entities[1], 0x00, 0x00, 0x00, 0xFF, (float)(worldSize), (float)(worldSize), (float)(-worldSize), 0.f);
		GraphicsComponent worldRightGraphics(&entities[1], 0x00, 0x00, 0x00, 0xFF, (float)(worldSize), (float)(worldSize), (float)(worldSize), 0.f);
		GraphicsComponent worldTopGraphics(&entities[1], 0x00, 0x00, 0x00, 0xFF, (float)((worldSize * 3)), (float)(worldSize), (float)(-worldSize), (float)(-worldSize));
		GraphicsComponent worldBottomGraphics(&entities[1], 0x00, 0x00, 0x00, 0xFF, (float)((worldSize * 3)), (float)(worldSize), (float)(-worldSize), (float)(worldSize));
		graphicsComponents[1] = worldLeftGraphics;
		graphicsComponents[2] = worldRightGraphics;
		graphicsComponents[3] = worldTopGraphics;
		graphicsComponents[4] = worldBottomGraphics;
		numGraphics += 4;

		// Tell world about components
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
		CreateBlock(600.f, (float)(worldSize - 500.f), 100.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock(500.f, (float)(worldSize - 400.f), 300.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock(400.f, (float)(worldSize - 300.f), 500.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock(300.f, (float)(worldSize - 200.f), 700.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock(0.f, (float)(worldSize - 100.f), (float)(worldSize), 50.f, 0x00, 0xAA, 0xAA);
	}

	return result;
}

bool EntityManager::instantiate(Entity *e, GraphicsComponent *g, ColliderComponent *c, PhysicsComponent *p, InputComponent *i)
{
	bool result = false;

	// TODO(don): Instantiate requested entity
	if (e == nullptr)// || g == nullptr)
	{
		std::cout << "EntityManager: received invalid instantiate" << std::endl;
	}
	else
	{
		std::cout << "EntityManager: received instantiate at (" << e->getX() << ", " << e->getY() << ")" << std::endl;
		CreateBlock((e->getX() + 50), (e->getY() - 50), 50.f, 50.f, 0xFF, 0x00, 0x00);
		result = true;
	}

	return result;
}

bool EntityManager::update(EntityInput* input, int NumInputs, uint32 DeltaTime, SDL_Renderer *renderer)
{
	// TODO(don): When the level is over set result to false
	bool result = true;

	float deltaTime = DeltaTime / 1000.f;

	// TODO(don): map input to appropriate player inputComponent
	// Process all inputs
	//for (int index = 0; index < numInputs; index++)
	//{
	// NOTE(don): process inputs according to a player to input map
	// TODO(don): remove temp keyboard/gamepad check
	if (numInputs > 1)
	{
		inputComponents[0].processInput(input[0], deltaTime);
	}
	else
	{
		inputComponents[0].processInput(input[1], deltaTime);
	}
	//}

	// Process all forces
	for (int index = 0; index < numPhysics; index++)
	{
		physicsComponents[index].update(deltaTime);
	}

	// TODO(don): Implement a broad stage pass to reduce the number of comparisons
	//    try binary space partitioning (bsp)
	// Process all colliders -- add any appropriate physics forces
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
	camCenterX = (int)(entities[0].getX());
	float targetY = entities[0].getY();
	if (camCenterY < targetY)
	{
		camCenterY += (int)camSpeed;
		if (camCenterY > targetY)
		{
			camCenterY = (int)targetY;
		}
	}
	else
	{
		camCenterY -= (int)camSpeed;
		if (camCenterY < targetY)
		{
			camCenterY = (int)targetY;
		}
	}

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

	return result;
}