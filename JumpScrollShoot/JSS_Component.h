//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_COMPONENT_H_GUARD
#define __JSS_COMPONENT_H_GUARD

// TODO(don): implement message union (see SDL_Event)
enum class MessageType { Physics, Health };
enum class MessageKey { Jump, Heal, Damage };

struct ComponentMessage
{
	MessageType type;
	MessageKey key;
	float value;
};

// NOTE(don): Component allows communication between concrete components and
// the concrete "owning" entity
class Component
{
public:
	virtual ~Component() {}

	virtual void receive(ComponentMessage message) = 0;
};

#endif