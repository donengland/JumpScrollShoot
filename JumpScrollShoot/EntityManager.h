//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_ENTITY_MANAGER_H_GUARD
#define __JSS_ENTITY_MANAGER_H_GUARD

#define MAX_ENTITIES 1000
#define MAX_PLAYERS 4

#include <vector>
#include "JSS_IEntityManager.h"
#include "JSS_InputComponent.h"
#include "JSS_GraphicsComponent.h"
#include "BulletComponent.h"
#include "SlimeBehavior.h"
#include "JSS_Entity.h"

typedef uint32_t uint32;

class EntityManager : public IEntityManager
{
public:
	EntityManager();
	~EntityManager();

	bool loadWorld();

	void CreateBlock(float x, float y, float w, float h, uint8 red = 0x00, uint8 green = 0x00, uint8 blue = 0x00, uint8 alpha = 0xFF);
	void CreateBullet(float x, float y, float w, float h, float angle, float magnitude, uint8 red = 0x00, uint8 green = 0x00, uint8 blue = 0x00, uint8 alpha = 0xFF);
	void CreateSlime(float x, float y);

	bool update(EntityInput* input, int NumInputs, uint32 DeltaTime, SDL_Renderer *renderer);

	bool instantiate(ComponentMessage msg);

	void deleteEntity(int id);

	void Shutdown();

private:
	void processDeleteEntities();

  int NextEntityId();
  int NextInputId();
  int NextColliderId();
  int NextGraphicsId();
  int NextPhysicsId();
  int NextBehaviorId();

	Entity entities[MAX_ENTITIES];
	GraphicsComponent graphicsComponents[MAX_ENTITIES];
	ColliderComponent colliderComponents[MAX_ENTITIES];
	PhysicsComponent physicsComponents[MAX_ENTITIES];
	InputComponent inputComponents[(MAX_PLAYERS + 1)];

	Component *behaviorComponents[MAX_ENTITIES];

	std::vector<int> deleteIds;

  std::vector<int> free_entities;
  std::vector<int> free_inputs;
  std::vector<int> free_colliders;
  std::vector<int> free_graphics;
  std::vector<int> free_physics;
  std::vector<int> free_behaviors;

	int numEntities;
	int numInputs;
	int numColliders;
	int numGraphics;
	int numPhysics;

	int numBehaviors;

	// TODO(don): Create world container for loading worlds
	int worldWidth;
	int worldHeight;

	// TODO(don): Create camera container?
	int camCenterX;
	int camCenterY;
	int camHalfWidth;
	int camHalfHeight;
	float camSpeed;
};

#endif