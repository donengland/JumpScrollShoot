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

#include "JSS_IEntityManager.h"
#include "JSS_InputComponent.h"
#include "JSS_GraphicsComponent.h"
#include "JSS_Entity.h"

typedef uint32_t uint32;

class EntityManager : public IEntityManager
{
public:
	EntityManager();

	bool loadWorld();

	void CreateBlock(float x, float y, float w, float h, uint8 red = 0x00, uint8 green = 0x00, uint8 blue = 0x00, uint8 alpha = 0xFF);

	bool update(EntityInput* input, int NumInputs, uint32 DeltaTime, SDL_Renderer *renderer);

	bool instantiate(Entity *e, GraphicsComponent *g = nullptr, ColliderComponent *c = nullptr, PhysicsComponent *p = nullptr, InputComponent *i = nullptr);

private:
	Entity entities[MAX_ENTITIES];
	InputComponent inputComponents[MAX_ENTITIES];
	GraphicsComponent graphicsComponents[MAX_ENTITIES];
	ColliderComponent colliderComponents[MAX_ENTITIES];
	PhysicsComponent physicsComponents[MAX_ENTITIES];

	int numEntities;
	int numInputs;
	int numColliders;
	int numGraphics;
	int numPhysics;

	// TODO(don): Create world container for loading worlds
	int worldSize;

	// TODO(don): Create camera container?
	int camCenterX;
	int camCenterY;
	int camHalfWidth;
	int camHalfHeight;
	float camSpeed;
};

#endif