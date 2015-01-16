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
	for (int index = 0; index < MAX_ENTITIES; index++)
	{
		behaviorComponents[index] = nullptr;
	}

	numEntities = 0;
	numInputs = 0;
	numColliders = 0;
	numGraphics = 0;
	numPhysics = 0;

	numBehaviors = 0;

	// TODO(don): Camera work
	camCenterX = 0;
	camCenterY = 0;
	camHalfWidth = 320;
	camHalfHeight = 240;
	camSpeed = 15.f;
};

EntityManager::~EntityManager()
{
	for (int index = 0; index < numBehaviors; index++)
	{
		if (behaviorComponents[index] != nullptr)
		{
			delete behaviorComponents[index];
		}
	}
}

void EntityManager::deleteEntity(int id)
{
	deleteIds.push_back(id);
}

void EntityManager::processDeleteEntities()
{
	for (auto id : deleteIds)
	{
		// Check for valid id
		if (id < numEntities)
		{
			// Copy last elements and repack arrays
			// TODO(don): Possibly remove physics creation coupling to collider, add via getComponent?
			// NOTE(don): Physics component needs to have its collider pointer updated

			// Get associated ids
			EntityIds ids = entities[id].getIds();

			//std::cout << "EntityManager: delete Entity: " << ids.entity <<
			//			 ", behavior: " << ids.behavior << ", collider: " << ids.collider << std::endl;

			Component *b = nullptr;

			// NOTE(don): Each array's number of elements gets reduced at the end
			//   of each block.  It may be cleaner to decrement at the start.
			if (ids.entity >= 0)
			{
				// Perform a swap if deleted element is not the end element
				if (ids.entity != (numEntities - 1))
				{
					// Copy last element into current hole
					entities[ids.entity] = entities[numEntities - 1];
				}
				else
				{
					entities[numEntities - 1] = Entity();
				}
				// Clear all pointers
				entities[ids.entity].clearComponents();
				// Update id
				entities[ids.entity].setId(ids.entity);
				numEntities--;
			}

			if (ids.graphics >= 0)
			{
				// Perform a swap if deleted element is not the end element
				if (ids.graphics != (numGraphics - 1))
				{
					// Copy last element into current hole
					graphicsComponents[ids.graphics] = graphicsComponents[numGraphics - 1];

					// Update entity pointer
					graphicsComponents[ids.graphics].setEntity(&entities[ids.entity]);
					
					// Point entity at new location
					entities[ids.entity].addComponent(&graphicsComponents[ids.graphics]);
					// Update Id
					entities[ids.entity].setGraphicsId(ids.graphics);
				}
				else
				{
					graphicsComponents[numGraphics - 1] = GraphicsComponent();
				}
				numGraphics--;
			}

			if (ids.collider >= 0)
			{
				// Perform a swap if deleted element is not the end element
				if (ids.collider != (numColliders - 1))
				{
					// Copy last element into current hole
					colliderComponents[ids.collider] = colliderComponents[numColliders - 1];

					// Update entity pointer
					colliderComponents[ids.collider].setEntity(&entities[ids.entity]);

					// Point entity at new location
					entities[ids.entity].addComponent(&colliderComponents[ids.collider]);
					// Update Id
					entities[ids.entity].setColliderId(ids.collider);
				}
				else
				{
					colliderComponents[ids.collider] = ColliderComponent();
				}
				numColliders--;
			}

			if (ids.physics >= 0)
			{
				// Perform a swap if deleted element is not the end element
				if (ids.physics != (numPhysics - 1))
				{
					// Copy last element into current hole
					physicsComponents[ids.physics] = physicsComponents[numPhysics - 1];

					// Update entity pointer
					physicsComponents[ids.physics].setEntity(&entities[ids.entity]);
					// Update collider pointer
					physicsComponents[ids.physics].setCollider(&colliderComponents[ids.collider]);

					// Point entity at new location
					entities[ids.entity].addComponent(&physicsComponents[ids.physics]);
					// Update Id
					entities[ids.entity].setPhysicsId(ids.physics);
				}
				else
				{
					physicsComponents[numPhysics - 1] = PhysicsComponent();
				}
				numPhysics--;
			}

			// NOTE(don): The input section may be replaced by a playerBehavior
			if (ids.input >= 0)
			{
				// Perform a swap if deleted element is not the end element
				if (ids.input != (numInputs - 1))
				{
					// Copy last element into current hole
					inputComponents[ids.input] = inputComponents[numInputs - 1];

					// Update entity pointer
					inputComponents[ids.input].setEntity(&entities[ids.entity]);

					// Point entity at new location
					entities[ids.entity].addComponent(&inputComponents[ids.input]);
					// Update Id
					entities[ids.entity].setInputId(ids.input);
				}
				else
				{
					inputComponents[numInputs - 1] = InputComponent();
				}
				numInputs--;
			}

			// NOTE(don): behavior component is handled as a pointer
			if (ids.behavior >= 0)
			{
				// Delete the behavior memory from the heap
				delete behaviorComponents[ids.behavior];

				// If the deleted element is not at the end of the array, do a swap
				if (ids.behavior != (numBehaviors - 1))
				{
					// Point current hole to last elements address on heap
					behaviorComponents[ids.behavior] = behaviorComponents[numBehaviors - 1];

					// Update entity pointer
					behaviorComponents[ids.behavior]->setEntity(&entities[ids.entity]);

					// Entities pointers were clear, reconnect this pointer
					entities[ids.entity].addComponent(behaviorComponents[ids.behavior]);
					// Update Id
					entities[ids.entity].setBehaviorId(ids.behavior);
				}
				behaviorComponents[numBehaviors - 1] = nullptr;
				numBehaviors--;
			}
		}
	}
	deleteIds.clear();
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

	// setup ids
	entities[numEntities - 1].setId(numEntities - 1);
	entities[numEntities - 1].setColliderId(numColliders - 1);
	entities[numEntities - 1].setGraphicsId(numGraphics - 1);
}

void EntityManager::CreateBullet(float x, float y, float w, float h, float angle, float magnitude, uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
	Entity block(this, x, y);
	entities[numEntities] = block;
	numEntities++;

	ColliderComponent collider(&entities[numEntities - 1], 0.f, 0.f, w, h, ColliderCategory::playerAttack);
	colliderComponents[numColliders] = collider;
	numColliders++;

	GraphicsComponent graphics(&entities[numEntities - 1], red, green, blue, alpha, w, h);
	graphicsComponents[numGraphics] = graphics;
	numGraphics++;

	BulletComponent *bullet = new BulletComponent(&entities[numEntities - 1], angle, magnitude);
	behaviorComponents[numBehaviors] = bullet;
	numBehaviors++;

	entities[numEntities - 1].addComponent(&colliderComponents[numColliders - 1]);
	entities[numEntities - 1].addComponent(&graphicsComponents[numGraphics - 1]);
	entities[numEntities - 1].addComponent(behaviorComponents[numBehaviors - 1]);

	// setup ids
	entities[numEntities - 1].setId(numEntities - 1);
	entities[numEntities - 1].setColliderId(numColliders - 1);
	entities[numEntities - 1].setGraphicsId(numGraphics - 1);
	entities[numEntities - 1].setBehaviorId(numBehaviors - 1);
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
		InputComponent playerInput(&entities[0], 200.f, 0.25f);
		inputComponents[0] = playerInput;
		numInputs++;

		// Tell entity[0] player one about components
		entities[0].addComponent(&inputComponents[0]);
		entities[0].addComponent(&colliderComponents[0]);
		entities[0].addComponent(&graphicsComponents[0]);
		entities[0].addComponent(&physicsComponents[0]);

		// setup ids
		entities[numEntities - 1].setId(numEntities - 1);
		entities[numEntities - 1].setColliderId(numColliders - 1);
		entities[numEntities - 1].setGraphicsId(numGraphics - 1);
		entities[numEntities - 1].setPhysicsId(numPhysics - 1);
		entities[numEntities - 1].setInputId(numInputs - 1);
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
		worldWidth = 5000;
		worldHeight = 480;

		// Add colliders on boundaries
		ColliderComponent worldLeftCollider(&entities[1], (float)(-worldWidth), 0.f, (float)(worldWidth), (float)(worldHeight));
		ColliderComponent worldRightCollider(&entities[1], (float)(worldWidth), 0.f, (float)(worldWidth), (float)(worldHeight));
		ColliderComponent worldTopCollider(&entities[1], (float)(-worldWidth), (float)(-worldHeight), (float)((worldWidth * 3)), (float)(worldHeight));
		ColliderComponent worldBottomCollider(&entities[1], (float)(-worldWidth), (float)(worldHeight), (float)((worldWidth * 3)), (float)(worldHeight));
		colliderComponents[1] = worldLeftCollider;
		colliderComponents[2] = worldRightCollider;
		colliderComponents[3] = worldTopCollider;
		colliderComponents[4] = worldBottomCollider;
		numColliders += 4;

		// Add Black Graphics Components for world edges
		GraphicsComponent worldLeftGraphics(&entities[1], 0x00, 0x00, 0x00, 0xFF, (float)(worldWidth), (float)(worldHeight), (float)(-worldWidth), 0.f);
		GraphicsComponent worldRightGraphics(&entities[1], 0x00, 0x00, 0x00, 0xFF, (float)(worldWidth), (float)(worldHeight), (float)(worldWidth), 0.f);
		GraphicsComponent worldTopGraphics(&entities[1], 0x00, 0x00, 0x00, 0xFF, (float)((worldWidth * 3)), (float)(worldHeight), (float)(-worldWidth), (float)(-worldHeight));
		GraphicsComponent worldBottomGraphics(&entities[1], 0x00, 0x00, 0x00, 0xFF, (float)((worldWidth * 3)), (float)(worldHeight), (float)(-worldWidth), (float)(worldHeight));
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
		CreateBlock((float)(worldWidth - 100.f), (float)(worldHeight - 500.f), 100.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock((float)(worldWidth - 200.f), (float)(worldHeight - 400.f), 200.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock((float)(worldWidth - 300.f), (float)(worldHeight - 300.f), 300.f, 100.f, 0x00, 0xFF, 0xFF);
		CreateBlock((float)(worldWidth - 400.f), (float)(worldHeight - 200.f), 400.f, 100.f, 0x00, 0xFF, 0xFF);
		int blockWidth = 100;
		for (int index = 0; index < (worldWidth / blockWidth); index++)
		{
			// Create Floor Blocks
			if (index % 2)
			{
				CreateBlock((float)(blockWidth * index), (float)(worldHeight - 100.f), (float)(blockWidth), 50.f, 0x00, 0xAA, 0xAA);
			}
			else
			{
				CreateBlock((float)(blockWidth * index), (float)(worldHeight - 100.f), (float)(blockWidth), 50.f, 0x00, 0xFF, 0xFF);
			}
		}
	}

	return result;
}

bool EntityManager::instantiate(ComponentMessage msg)
{
	bool result = false;
	if (msg.type == MessageType::Instantiate)
	{
		if (msg.key == MessageKey::Bullet)
		{
			CreateBullet((msg.x + ((msg.value == 0.f) ? 50 : 0)),	// X Position
						 (msg.y + 25),								// Y Position
						 5.f, 5.f,									// Size
						 msg.value,									// Angle | where 0.f is right, 90.f is up
						 500.f,										// Speed (pixels per second)
						 0xFF, 0x00, 0x00);							// Color
			result = true;
		}
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

	// Process all behaviors
	// NOTE(don): this area cannot be cache aligned for a long time
	for (int index = 0; index < numBehaviors; index++)
	{
		behaviorComponents[index]->update(deltaTime);
	}

	// Process all forces
	for (int index = 0; index < numPhysics; index++)
	{
		physicsComponents[index].update(deltaTime);
	}

	// TODO(don): Implement a broad stage pass to reduce the number of comparisons
	//    try binary space partitioning (bsp)
	// Process all colliders -- add any appropriate physics forces
	for (int index = 0; index < numColliders; index++)
	{
		// Note, may want to expand collision with enter, stay and exit flags/functions
		colliderComponents[index].resetCollisions();
	}
	for (int primary = 0; primary < numColliders; primary++)
	{
		ColliderCategory primaryCat = colliderComponents[primary].getCategory();

		//if (primaryCat != ColliderCategory::immobile)
		//{

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
					if (primaryCat != ColliderCategory::immobile)
					{
						colliderComponents[primary].resolveCollision(colliderComponents[secondary]);
					}

					// TODO(don): Profiling - is it better to do double the checks in sequence or notify secondary immediately?
					ColliderCategory secondaryCat = colliderComponents[secondary].getCategory();
					if (secondaryCat != ColliderCategory::immobile)
					{
						// Notify other component of collision
						colliderComponents[secondary].resolveCollision(colliderComponents[primary]);
					}
				}
			}
		//}
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
	else if ((camCenterX + camHalfWidth) > worldWidth)
	{
		camCenterX = worldWidth - camHalfWidth;
	}
	if ((camCenterY - camHalfHeight) < 0)
	{
		camCenterY = camHalfHeight;
	}
	else if ((camCenterY + camHalfHeight) > worldHeight)
	{
		camCenterY = worldHeight - camHalfHeight;
	}
	
	// Process all deletions before drawing
	processDeleteEntities();

	// Process all rendering
	int xOffset = camCenterX - camHalfWidth;
	int yOffset = camCenterY - camHalfHeight;
	for (int index = 0; index < numGraphics; index++)
	{
		graphicsComponents[index].render(renderer, xOffset, yOffset);
	}

	return result;
}