//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_GAMEPAD_INPUT_COMPONENT_H_GUARD
#define __JSS_GAMEPAD_INPUT_COMPONENT_H_GUARD

#include "JSS_Component.h"
#include "JSS_Entity.h"

class GamepadInputComponent : public Component
{
public:
	void receive(ComponentMessage message);
private:
	Entity *entity;
};

#endif