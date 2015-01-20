//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <iostream>
#include "BulletComponent.h"

BulletComponent::BulletComponent()
{
  entity_ = nullptr;
  active_ = false;
	xVel_ = 0.f;
	yVel_ = 0.f;
};

BulletComponent::BulletComponent(Entity *entity, int id, float Angle, float Magnitude)
{
	entity_ = entity;
	id_ = id;
	xVel_ = (float)((Cos(Angle)) * Magnitude);
  yVel_ = (float)((Sin(Angle)) * Magnitude);
  active_ = true;
};

void BulletComponent::setEntity(Entity *entity)
{
	entity_ = entity;
	entity_->setBehavior(this, id_);
}

void BulletComponent::setId(int id)
{
	id_ = id;
	entity_->setBehavior(this, id_);
}
int BulletComponent::getId() { return id_; }

bool BulletComponent::get_active() { return active_; }
void BulletComponent::set_active(bool active){ active_ = active; }

void BulletComponent::receive(ComponentMessage message)
{

};

void BulletComponent::update(float deltaTime, float *playerXY, int numPlayers)
{
	entity_->changeX((xVel_ * deltaTime));
	entity_->changeY((yVel_ * deltaTime));
};