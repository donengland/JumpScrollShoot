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

// TODO(don): Implement a handler system, indirection for the actual indexes to survive moves
void EntityManager::processDeleteEntities()
{
	for (auto id : deleteIds)
	{
		// Check for valid id
		if (id < numEntities) {
			// Copy last elements and repack arrays
			// TODO(don): Possibly remove physics creation coupling to collider, add via getComponent?
			// NOTE(don): Physics component needs to have its collider pointer updated

			// Get associated ids
			EntityIds ids = entities[id].getIds();
      if (1)
      {
        if (ids.entity >= 0)
        {
          entities[ids.entity].set_active(false);
          free_entities.push_back(ids.entity);
        }
        if (ids.input >= 0)
        {
          inputComponents[ids.input].set_active(false);
          free_inputs.push_back(ids.input);
        }
        if (ids.graphics >= 0)
        {
          graphicsComponents[ids.graphics].set_active(false);
          free_graphics.push_back(ids.graphics);
        }
        if (ids.collider >= 0)
        {
          colliderComponents[ids.collider].set_active(false);
          free_colliders.push_back(ids.collider);
        }
        if (ids.physics >= 0)
        {
          physicsComponents[ids.physics].set_active(false);
          free_physics.push_back(ids.physics);
        }
        if (ids.behavior >= 0)
        {
          behaviorComponents[ids.behavior]->set_active(false);
          free_behaviors.push_back(ids.behavior);
        }
      }
      else
      {
        EntityIds movedEntity = {};
        movedEntity.behavior = -1;
        movedEntity.collider = -1;
        movedEntity.entity = -1;
        movedEntity.graphics = -1;
        movedEntity.input = -1;
        movedEntity.physics = -1;

        //std::cout << "EntityManager: delete Entity: " << ids.entity <<
        //			 ", behavior: " << ids.behavior << ", collider: " << ids.collider << std::endl;

        //Component *b = nullptr;

        // NOTE(don): Each array's number of elements gets reduced at the end
        //   of each block.  It may be cleaner to decrement at the start.
        if (ids.entity >= 0)
        {
          // Perform a swap if deleted element is not the end element
          if (ids.entity != (numEntities - 1))
          {
            // Copy last element into current hole
            entities[ids.entity] = entities[numEntities - 1];

            // Entity has swapped, we need to update all of it's components to point here
            movedEntity = entities[ids.entity].getIds();

            // NOTE(don): updating id forces all components to update their links to this entity
            entities[ids.entity].setId(ids.entity);
            //entities[numEntities - 1] = Entity();
          }
          else
          {
            entities[numEntities - 1] =  Entity();
          }
          numEntities--;
        }

        if (ids.graphics >= 0)
        {
          // Perform a swap if deleted element is not the end element
          if (ids.graphics != (numGraphics - 1))
          {
            // Copy last element into current hole
            graphicsComponents[ids.graphics] = graphicsComponents[numGraphics - 1];
            graphicsComponents[ids.graphics].setId(ids.graphics);
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
            colliderComponents[ids.collider].setId(ids.collider);
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
            physicsComponents[ids.physics].setId(ids.physics);

            if (movedEntity.collider == (numColliders))
            {
            // Tell physics component that the collider pointer is out of date
            physicsComponents[ids.physics].updateCollider();
            }
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
            inputComponents[ids.input].setId(ids.input);
          }
          else
          {
            inputComponents[numInputs - 1] = InputComponent();
          }
          numInputs--;
        }

        // NOTE(don): behavior component is a pointer to Component Interface
        if (ids.behavior >= 0)
        {
          // Delete the behavior memory from the heap
          delete behaviorComponents[ids.behavior];
          behaviorComponents[ids.behavior] = nullptr;

          // If the deleted element is not at the end of the array, do a swap
          if (ids.behavior != (numBehaviors - 1))
          {
            // Point to last elements address on heap (Component)
            behaviorComponents[ids.behavior] = behaviorComponents[numBehaviors - 1];
            behaviorComponents[ids.behavior]->setId(ids.behavior);
            behaviorComponents[numBehaviors - 1] = nullptr;
          }
          numBehaviors--;
        }
      }
		}
	}
	deleteIds.clear();
}

int EntityManager::NextEntityId()
{
  int entity_id;
  if (free_entities.size() > 0)
  {
    entity_id = free_entities.back();
    free_entities.pop_back();
  }
  else
  {
    entity_id = numEntities;
    numEntities++;
  }
  return entity_id;
}

int EntityManager::NextColliderId()
{
  int collider_id;
  if (free_colliders.size() > 0)
  {
    collider_id = free_colliders.back();
    free_colliders.pop_back();
  }
  else
  {
    collider_id = numColliders;
    numColliders++;
  }
  return collider_id;
}

int EntityManager::NextGraphicsId()
{
  int graphics_id;
  if (free_graphics.size() > 0)
  {
    graphics_id = free_colliders.back();
    free_colliders.pop_back();
  }
  else
  {
    graphics_id = numGraphics;
    numGraphics++;
  }
  return graphics_id;
}

int EntityManager::NextPhysicsId()
{
  int physics_id;
  if (free_physics.size() > 0)
  {
    physics_id = free_physics.back();
    free_physics.pop_back();
  }
  else
  {
    physics_id = numPhysics;
    numPhysics++;
  }
  return physics_id;
}

int EntityManager::NextBehaviorId()
{
  int behavior_id;
  if (free_behaviors.size() > 0)
  {
    behavior_id = free_behaviors.back();
    free_behaviors.pop_back();
    delete behaviorComponents[behavior_id];
    behaviorComponents[behavior_id] = nullptr;
  }
  else
  {
    behavior_id = numBehaviors;
    numBehaviors++;
  }
  return behavior_id;
}

void EntityManager::CreateBlock(float x, float y, float w, float h, uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
  if (numEntities < MAX_ENTITIES)
  {
    int entity_id = NextEntityId();
    int collider_id = NextColliderId();
    int graphics_id = NextGraphicsId();

    Entity block(this, entity_id, x, y);
    entities[entity_id] = block;

    ColliderComponent collider(&entities[entity_id], collider_id, w, h);
    colliderComponents[collider_id] = collider;

    GraphicsComponent graphics(&entities[entity_id], graphics_id, red, green, blue, alpha, w, h);
    graphicsComponents[graphics_id] = graphics;

    entities[entity_id].setCollider(&colliderComponents[collider_id], collider_id);
    entities[entity_id].setGraphics(&graphicsComponents[graphics_id], graphics_id);
  }
}

void EntityManager::CreateBullet(float x, float y, float w, float h, float angle, float magnitude, uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
  if (numEntities < MAX_ENTITIES)
  {
    int entity_id = NextEntityId();
    int collider_id = NextColliderId();
    int graphics_id = NextGraphicsId();
    int behavior_id = NextBehaviorId();

    Entity bullet(this, entity_id, x, y);
    entities[entity_id] = bullet;

    ColliderComponent collider(&entities[entity_id], collider_id, w, h, ColliderCategory::playerAttack);
    colliderComponents[collider_id] = collider;

    GraphicsComponent graphics(&entities[entity_id], graphics_id, red, green, blue, alpha, w, h);
    graphicsComponents[graphics_id] = graphics;

    BulletComponent *behavior = new BulletComponent(&entities[entity_id], behavior_id, angle, magnitude);
    behaviorComponents[behavior_id] = behavior;

    entities[entity_id].setCollider(&colliderComponents[collider_id], collider_id);
    entities[entity_id].setGraphics(&graphicsComponents[graphics_id], graphics_id);
    entities[entity_id].setBehavior(behaviorComponents[behavior_id], behavior_id);
  }
}

void EntityManager::CreateSlime(float x, float y)
{
  if (numEntities < MAX_ENTITIES)
  {
    int entity_id = NextEntityId();
    int collider_id = NextColliderId();
    int graphics_id = NextGraphicsId();
    int physics_id = NextPhysicsId();
    int behavior_id = NextBehaviorId();

    float w = 25.f;
    float h = 25.f;

    Entity enemy(this, entity_id, x, y);
    entities[entity_id] = enemy;

    ColliderComponent collider(&entities[entity_id], collider_id, w, h, ColliderCategory::enemy);
    colliderComponents[collider_id] = collider;

    GraphicsComponent graphics(&entities[entity_id], graphics_id, 0x00, 0xAA, 0x00, 0xFF, w, h);
    graphicsComponents[graphics_id] = graphics;

    PhysicsComponent slimePhysics(&entities[entity_id], &colliderComponents[collider_id], physics_id);
    physicsComponents[physics_id] = slimePhysics;

    SlimeBehavior *slime = new SlimeBehavior(&entities[entity_id], behavior_id);
    behaviorComponents[behavior_id] = slime;

    entities[entity_id].setCollider(&colliderComponents[collider_id], collider_id);
    entities[entity_id].setGraphics(&graphicsComponents[graphics_id], graphics_id);
    entities[entity_id].setPhysics(&physicsComponents[physics_id], physics_id);
    entities[entity_id].setBehavior(behaviorComponents[behavior_id], behavior_id);
  }
}

bool EntityManager::loadWorld()
{
	bool result = false;

	// TODO(don): Load world from file/database/etc

	// Create player entity
	{
		// TODO(don): reserve first 4 entities for players?
		Entity player(this, 0, 100.f, 300.f);
		entities[0] = player;
		numEntities++;

		// TODO(don): Resolve width and height at a higher level
		// ColliderComponent created and copied over element 0 player one
		ColliderComponent playerCollider(&entities[0], 0, 50.f, 50.f, ColliderCategory::player);
		colliderComponents[0] = playerCollider;
		numColliders++;

		// GraphicsComponent created and copied over element 0 player one
		GraphicsComponent playerGraphics(&entities[0], 0, 0x00, 0x00, 0xFF, 0xFF, 50.f, 50.f);
		graphicsComponents[0] = playerGraphics;
		numGraphics++;

		// PhysicsComponent created and copied over element 0 player one
		PhysicsComponent playerPhysics(&entities[0], &colliderComponents[0], 0);
		physicsComponents[0] = playerPhysics;
		numPhysics++;

		// InputComponent created and copied over element 0 player one
		InputComponent playerInput(&entities[0], 0, 200.f, 0.25f);
		inputComponents[0] = playerInput;
		numInputs++;

		// Tell entity[0] player one about components
		entities[0].setInput(&inputComponents[0], 0);
		entities[0].setCollider(&colliderComponents[0], 0);
		entities[0].setGraphics(&graphicsComponents[0], 0);
		entities[0].setPhysics(&physicsComponents[0], 0);
	}

	// TODO(don): world needs edge bounds only, camera can restrict movement from there
	//    Perhaps a secondary grid for camera restrictions?
	// NOTE(don): world entity for initial colliderComponent tests
	// Create World Entity
	{
		// NOTE(don): Test different world sizes
		worldWidth = 1000;
		worldHeight = 480;

		Entity worldLeft(this, 1, (float)(-worldWidth), 0.f);
		Entity worldRight(this, 2, (float)(worldWidth), 0.f);
		Entity worldTop(this, 3, (float)(-worldWidth), (float)(-worldHeight));
		Entity worldBottom(this, 4, (float)(-worldWidth), (float)(worldHeight));
		entities[1] = worldLeft;
		entities[2] = worldRight;
		entities[3] = worldTop;
		entities[4] = worldBottom;
		numEntities += 4;

		// Add colliders on boundaries
		ColliderComponent worldLeftCollider(&entities[1], 1, (float)(worldWidth), (float)(worldHeight));
		ColliderComponent worldRightCollider(&entities[2], 2, (float)(worldWidth), (float)(worldHeight));
		ColliderComponent worldTopCollider(&entities[3], 3, (float)((worldWidth * 3)), (float)(worldHeight));
		ColliderComponent worldBottomCollider(&entities[4], 4, (float)((worldWidth * 3)), (float)(worldHeight));
		colliderComponents[1] = worldLeftCollider;
		colliderComponents[2] = worldRightCollider;
		colliderComponents[3] = worldTopCollider;
		colliderComponents[4] = worldBottomCollider;
		numColliders += 4;

		// Add Black Graphics Components for world edges
		GraphicsComponent worldLeftGraphics(&entities[1], 1, 0x00, 0x00, 0x00, 0xFF, (float)(worldWidth), (float)(worldHeight));
		GraphicsComponent worldRightGraphics(&entities[2], 2, 0x00, 0x00, 0x00, 0xFF, (float)(worldWidth), (float)(worldHeight));
		GraphicsComponent worldTopGraphics(&entities[3], 3, 0x00, 0x00, 0x00, 0xFF, (float)((worldWidth * 3)), (float)(worldHeight));
		GraphicsComponent worldBottomGraphics(&entities[4], 4, 0x00, 0x00, 0x00, 0xFF, (float)((worldWidth * 3)), (float)(worldHeight));
		graphicsComponents[1] = worldLeftGraphics;
		graphicsComponents[2] = worldRightGraphics;
		graphicsComponents[3] = worldTopGraphics;
		graphicsComponents[4] = worldBottomGraphics;
		numGraphics += 4;

		// Tell world about components
		entities[1].setCollider(&colliderComponents[1], 1);
		entities[2].setCollider(&colliderComponents[2], 2);
		entities[3].setCollider(&colliderComponents[3], 3);
		entities[4].setCollider(&colliderComponents[4], 4);
		entities[1].setGraphics(&graphicsComponents[1], 1);
		entities[2].setGraphics(&graphicsComponents[2], 2);
		entities[3].setGraphics(&graphicsComponents[3], 3);
		entities[4].setGraphics(&graphicsComponents[4], 4);
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


	// TODO(don): Remove temp slime spawner
	float slimeRate = 10.f;
	static float slimeTimer = 0.f;
	if (slimeTimer <= 0.f)
	{
		CreateSlime((entities[0].getX() + 250), entities[0].getY());
		slimeTimer = slimeRate;
	}
	else
	{
		slimeTimer -= deltaTime;
	}
	
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

	// TODO(don): Temp player position passing into enemy behaviors
	//    Player should broadcast a location message with a Rect for collision checking
	//    any collider within the Rect will receive playerClose message.
	float playerPos[2];
	playerPos[0] = entities[0].getX();
	playerPos[1] = entities[1].getY();
	float *playerXY = playerPos;
	int numPlayers = 1;

	// Process all behaviors
	// NOTE(don): this area cannot be cache aligned for a long time
	for (int index = 0; index < numBehaviors; index++)
  {
    if (behaviorComponents[index]->get_active())
    {
      behaviorComponents[index]->update(deltaTime, playerXY, numPlayers);
    }
	}

	// Process all forces
	for (int index = 0; index < numPhysics; index++)
	{
    if (physicsComponents[index].get_active())
    {
      physicsComponents[index].update(deltaTime, playerXY, numPlayers);
    }
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
    if (colliderComponents[primary].get_active())
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

	// Process all rendering
	int xOffset = camCenterX - camHalfWidth;
	int yOffset = camCenterY - camHalfHeight;
	for (int index = 0; index < numGraphics; index++)
	{
    if (graphicsComponents[index].get_active())
    {
      graphicsComponents[index].render(renderer, xOffset, yOffset);
    }
  }

  // Process all deletions before drawing
  processDeleteEntities();

	return result;
}