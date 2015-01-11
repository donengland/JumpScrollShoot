//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JUMP_SCROLL_SHOOT_H_GUARD
#define __JUMP_SCROLL_SHOOT_H_GUARD

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "JSS_Entity.h"
#include "JSS_TransformComponent.h"
#include "JSS_InputComponent.h"
#include "JSS_ColliderComponent.h"

#define MAX_ENTITY_INPUTS 5

#define MAX_ENTITIES 1000

typedef unsigned __int32 uint32;

class JumpScrollShoot
{
public:
	JumpScrollShoot();

	void GameLoop(EntityInput* input, int numInputs, uint32 deltaTime, SDL_Renderer *renderer);
	void GameShutdown();
private:
	Entity entities[MAX_ENTITIES];
	TransformComponent transformComponents[MAX_ENTITIES];
	InputComponent inputComponents[MAX_ENTITIES];
	ColliderComponent colliderComponents[MAX_ENTITIES];

	int numEntities;
	int numTransforms;
	int numInputs;
	int numColliders;
};

#endif