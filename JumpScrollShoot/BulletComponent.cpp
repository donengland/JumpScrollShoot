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
	entity = nullptr;
	xVel = 0.f;
	yVel = 0.f;
};

BulletComponent::BulletComponent(Entity *e, float Angle, float Magnitude)
{
	entity = e;
	xVel = (float)((Cos(Angle)) * Magnitude);
	yVel = (float)((Sin(Angle)) * Magnitude);
};

void BulletComponent::setEntity(Entity *bulletEntity)
{
	entity = bulletEntity;
}

void BulletComponent::receive(ComponentMessage message)
{

};

void BulletComponent::update(float deltaTime)
{
	entity->changeX((xVel * deltaTime));
	entity->changeY((yVel * deltaTime));
};