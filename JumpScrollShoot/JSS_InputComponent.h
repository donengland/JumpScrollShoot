//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_INPUT_COMPONENT_H_GUARD
#define __JSS_INPUT_COMPONENT_H_GUARD

#include "JSS_Entity.h"
#include "JSS_Component.h"
#include "JSS_PhysicsComponent.h"

struct EntityInput
{
	int jump;

	bool shoot;

	bool up;
	bool down;
	bool left;
	bool right;
};

class InputComponent : public Component
{
public:
	InputComponent() { speed = 0.0f; }
	InputComponent(Entity *inputEntity, float Speed, float FireRate);

	void setEntity(Entity *inputEntity);

	void receive(ComponentMessage message);
	void processInput(EntityInput input, float deltaTime);
	void update(float deltaTime);

private:
	Entity *entity;
	float speed;

	float firing;
	float fireRate;
	bool facingRight;

	bool jumping;
};

#endif