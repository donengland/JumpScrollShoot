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

#include "JSS_InputComponent.h"
#include "JSS_GraphicsComponent.h"
#include "JSS_Entity.h"

class EntityManager
{
public:
	EntityManager();

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
};

#endif