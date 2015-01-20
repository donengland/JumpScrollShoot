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

// TODO(don): Change this type name
enum class ColliderCategory { immobile, mobile, player, enemy, playerAttack, enemyAttack, trigger };

class ColliderComponent : public Component
{
public:
	ColliderComponent();
	ColliderComponent(Entity *entity, int id,
					  float width = 0.0f, float height = 0.0f,
					  ColliderCategory category = ColliderCategory::immobile,
					  float localX = 0.0f, float localY = 0.0f);

	void setEntity(Entity *ColliderEntity);

	void receive(ComponentMessage message);
	void update(float deltaTime, float *playerXY, int numPlayers);

	void resetCollisions();
	void resolveCollision(ColliderComponent &other);

  bool get_active();
  void set_active(bool active);

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

	void setId(int myId);
	int getId();

	float getWidth();
	float getHeight();

	void setWidth(float Width);
	void setHeight(float Height);

	ColliderCategory getCategory();
	void setCategory(ColliderCategory Category);

private:
	Entity *entity_;
	ColliderCategory category_;
  bool active_;
	int id_;
	float x_;
	float y_;

	float width_;
	float height_;

	bool right_;
	bool left_;
	bool above_;
	bool below_;

	bool grounded_;
	bool colliding_;
};

#endif