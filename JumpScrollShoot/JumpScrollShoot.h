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
#include "JSS_GraphicsComponent.h"
#include "JSS_PhysicsComponent.h"

#define MAX_ENTITY_INPUTS 5

#define MAX_ENTITIES 1000

typedef unsigned __int32 uint32;

class JumpScrollShoot
{
public:
	JumpScrollShoot();

	void GameInit();
	void GameLoop(EntityInput* input, int numInputs, uint32 deltaTime, SDL_Renderer *renderer);
	void GameShutdown();

private:
	void CreateBlock(float x, float y, float w, float h, uint8 red = 0x00, uint8 green = 0x00, uint8 blue = 0x00, uint8 alpha = 0xFF);

	Entity entities[MAX_ENTITIES];
	TransformComponent transformComponents[MAX_ENTITIES];
	InputComponent inputComponents[MAX_ENTITIES];
	ColliderComponent colliderComponents[MAX_ENTITIES];
	GraphicsComponent graphicsComponents[MAX_ENTITIES];
	PhysicsComponent physicsComponents[MAX_ENTITIES];

	int numEntities;
	int numTransforms;
	int numInputs;
	int numColliders;
	int numGraphics;
	int numPhysics;

	// TODO(don): Create world container for loading worlds
	int worldSize;

	// TODO(don): Create camera container?
	int camCenterX = 0;
	int camCenterY = 0;
	int camHalfWidth = 320;
	int camHalfHeight = 240;
	float camSpeed;

	bool init;
};

#endif