//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_COMPONENT_H_GUARD
#define __JSS_COMPONENT_H_GUARD

enum class MessageType { Health, Damage };

struct ComponentMessage
{
	MessageType type;
	void* content;
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