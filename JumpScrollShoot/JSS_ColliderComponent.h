//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef JSS_COLLIDER_COMPONENT_H_GUARD
#define JSS_COLLIDER_COMPONENT_H_GUARD

#include "JSS_Entity.h"
#include "JSS_TransformComponent.h"
//#include "JSS_PhysicsComponent.h"

// TODO(don): Change this type name
enum class ColliderCategory { immobile, mobile, player, enemy, playerAttack, enemyAttack, trigger };

class ColliderComponent : public Component
{
public:
	ColliderComponent();
	ColliderComponent(Entity *ColliderEntity,
					  TransformComponent *Transform,
					  float localX = 0.0f, float localY = 0.0f,
					  float Width = 0.0f, float Height = 0.0f,
					  ColliderCategory Category = ColliderCategory::immobile);

	void receive(ComponentMessage message);

	void resetCollisions();
	void resolveCollision(ColliderComponent &other);

	bool isGrounded();
	bool isColliding();

	float getLocalX();
	float getLocalY();

	float getMinX();
	float getMaxX();

	float getMinY();
	float getMaxY();

	void setX(float X);
	void setY(float Y);

	float getWidth();
	float getHeight();

	void setWidth(float Width);
	void setHeight(float Height);

	ColliderCategory getCategory();
	void setCategory(ColliderCategory Category);

private:
	Entity *entity;
	TransformComponent *transform;
	ColliderCategory category;
	float x;
	float y;

	float width;
	float height;

	bool right;
	bool left;
	bool above;
	bool below;

	bool grounded;
	bool colliding;
};

#endif