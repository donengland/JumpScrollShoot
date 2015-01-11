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

// TODO(don): Change this type name
enum class ColliderCategory { immobile, mobile, player, enemy, playerAttack, enemyAttack };

class ColliderComponent : public Component
{
public:
	ColliderComponent(TransformComponent *Transform) { transform = Transform; }
	void receive(ComponentMessage message);

	float getX() { return x; }
	float getY() { return y; }

	void setX(float X) { x = X; }
	void setY(float Y) { y = Y; }

	float getWidth() { return width; }
	float getHeight() { return height; }

	void setWidth(float Width) { width = Width; }
	void setHeight(float Height) { height = Height; }

	ColliderCategory getCategory() { return category; }
	void setCategory(ColliderCategory Category) { category = Category; }

private:
	Entity *entity;
	TransformComponent *transform;
	ColliderCategory category;
	float x;
	float y;

	float width;
	float height;

};

#endif