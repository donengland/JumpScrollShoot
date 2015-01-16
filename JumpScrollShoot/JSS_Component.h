//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_COMPONENT_H_GUARD
#define __JSS_COMPONENT_H_GUARD

class Entity;

// TODO(don): implement message union (see SDL_Event)
enum class MessageType { Instantiate, Physics, Health, DeleteMe };
enum class MessageKey { Jump, Bullet, Heal, Damage };

struct ComponentMessage
{
	MessageType type;
	MessageKey key;
	float x;
	float y;
	float value;
};

// NOTE(don): Component allows communication between concrete components and
// the concrete entity that points to it
class Component
{
public:
	virtual ~Component() {}

	virtual void receive(ComponentMessage message) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void setEntity(Entity *entity) = 0;
};

#endif