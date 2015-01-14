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
#include "JSS_InputComponent.h"
#include "JSS_ColliderComponent.h"
#include "JSS_GraphicsComponent.h"
#include "JSS_PhysicsComponent.h"
#include "EntityManager.h"

#define MAX_ENTITY_INPUTS 5

#define MAX_ENTITIES 1000

typedef unsigned __int32 uint32;

class JumpScrollShoot
{
public:
	JumpScrollShoot();

	void GameLoop(EntityInput* input, int numInputs, uint32 deltaTime, SDL_Renderer *renderer);

private:
	EntityManager manager;

	bool init;
};

#endif