//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_INPUT_COMPONENT_H_GUARD
#define __JSS_INPUT_COMPONENT_H_GUARD

#include "JSS_Component.h"
#include "JSS_TransformComponent.h"
#include "JSS_Entity.h"

struct EntityInput
{
	bool up;
	bool down;
	bool left;
	bool right;

	bool jump;
};

class InputComponent : public Component
{
public:
	InputComponent() { speed = 0.0f; }
	InputComponent(TransformComponent *Transform, float Speed) { transform = Transform; speed = Speed; }

	void receive(ComponentMessage message);
	void processInput(EntityInput input, __int32 deltaTime);
private:
	Entity *entity;
	TransformComponent *transform;
	float speed;
};

#endif