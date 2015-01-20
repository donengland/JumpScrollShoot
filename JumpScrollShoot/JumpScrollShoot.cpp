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

  static don_entity_component::Entity test;
	
	// TODO(don): look up branching rules.  Is it better to test init true?
	if (init == false)
	{
		// TODO(don): Starting Menu

		// TODO(don): Select a level
		
		// TODO(don): Load the appropriate level
		manager.loadWorld();
		init = true;

    don_entity_component::RectangleGraphicsComponent rect(renderer);
    std::unique_ptr<don_entity_component::RectangleGraphicsComponent> unique_rect(new don_entity_component::RectangleGraphicsComponent(renderer));
    test.AddComponent(std::move(unique_rect));
    test.set_x_position(100);
    test.set_y_position(100);
	}
	else
	{
    test.Update(deltaTime);

		// NOTE(don): if the level has ended manager.update() returns false
		if (!manager.update(input, NumInputs, DeltaTime, renderer))
		{
			init = false;
		}
	}
	
}
