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
	InputComponent() { speed_ = 0.0f; }
	InputComponent(Entity *entity, int id, float speed, float fireRate);

	void setEntity(Entity *entity);

	void receive(ComponentMessage message);
	void processInput(EntityInput input, float deltaTime);
	void update(float deltaTime, float *playerXY, int numPlayers);

  bool get_active();
  void set_active(bool active);

	void setId(int id);
	int getId();

private:
	Entity *entity_;
  bool active_;
	int id_;
	float speed_;

	float firing_;
	float fireRate_;
	bool facingRight_;

	bool jumping_;
};

#endif