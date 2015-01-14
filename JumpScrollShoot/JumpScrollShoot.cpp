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
	init = false;
}



void JumpScrollShoot::GameLoop(EntityInput* input, int NumInputs, uint32 DeltaTime, SDL_Renderer *renderer)
{
	// NOTE(don): convert deltaTime into seconds
	float deltaTime = DeltaTime / 1000.f;
	
	// TODO(don): look up branching rules.  Is it better to test init true?
	if (init == false)
	{
		// TODO(don): Starting Menu

		// TODO(don): Select a level
		
		// TODO(don): Load the appropriate level
		manager.loadWorld();
		init = true;
	}
	else
	{
		// NOTE(don): if the level has ended manager.update() returns false
		if (!manager.update(input, NumInputs, DeltaTime, renderer))
		{
			init = false;
		}
	}
	
}
