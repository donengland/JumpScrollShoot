//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <iostream>
#include <cmath>
#include "JSS_ColliderComponent.h"


ColliderComponent::ColliderComponent()
{
	entity_ = nullptr;
}

ColliderComponent::ColliderComponent(Entity *entity, int id,
									 float width, float height,
									 ColliderCategory category,
									 float localX, float localY)
{
	entity_ = entity;
	id_ = id;
	//entity->setColliderId(id);
	category_ = category;

	x_ = localX;
	y_ = localY;

	width_ = width;
	height_ = height;

	right_ = false;
	left_ = false;
	above_ = false;
	below_ = false;
	grounded_ = false;
	colliding_ = false;
}

void ColliderComponent::setEntity(Entity *ColliderEntity)
{
	entity_ = ColliderEntity;
	entity_->setCollider(this, id_);
}

void ColliderComponent::setId(int id)
{
	id_ = id;
	entity_->setColliderId(id_);
}

int ColliderComponent::getId()
{
	return id_;
}

void ColliderComponent::resetCollisions()
{
	right_ = false;
	left_ = false;
	above_ = false;
	below_ = false;
	grounded_ = false;
	colliding_ = false;
}

void ColliderComponent::resolveCollision(ColliderComponent &other)
{
	// We had a collision with another Collider
	colliding_ = true;
	
	if ((category_ == ColliderCategory::playerAttack) && (other.category_ == ColliderCategory::immobile))
	{
		//std::cout << "Collider Component:Sending DeleteMe Message" << std::endl;
		ComponentMessage msg;
		msg.type = MessageType::DeleteMe;
		msg.key = MessageKey::Damage;
		msg.value = 0.f;
		entity_->broadcast(msg);
	}
	else if (other.category_ == ColliderCategory::immobile)
	{
		// Flag for possibly being completely inside the other collider
		bool inside = false;
		float changeX = 100000.0f;
		float changeY = 100000.0f;
		if (getMaxX() > other.getMaxX())
		{
			// Other to my left
			left_ = true;
			changeX = (other.getMaxX() - getMinX());
		}
		else if (getMinX() < other.getMinX())
		{
			// Other to my right
			right_ = true;
			changeX = (other.getMinX() - getMaxX());
		}
		else
		{
			// Other on left and right
			inside = true;
		}
		if (getMaxY() > other.getMaxY())
		{
			// Other above me
			above_ = true;
			changeY = (other.getMaxY() - getMinY());
		}
		else if (getMinY() < other.getMinY())
		{
			// Consider other below me
			below_ = true;
			changeY = (other.getMinY() - getMaxY());
		}
		else
		{
			if (inside)
			{
				inside = false;
				left_ = true;
				right_ = true;
				above_ = true;
				below_ = true;
				// we are completely inside the other collider!!!
				// TODO(don): Find the shortest way out (using X only temporarily)
				float rightDistance = (other.getMaxX() - getMaxX());
				float leftDistance = (getMinX() - other.getMinX());
				if (rightDistance > leftDistance)
				{
					changeX = -leftDistance;
				}
				else
				{
					changeX = rightDistance;
				}
			}
		}		
		if (abs(changeX) < abs(changeY))
		{
			entity_->changeX(changeX);
		}
		else
		{
			entity_->changeY(changeY);
		}

		if (below_ && (abs(getMaxY() - other.getMinY()) < .5f))
		{
			grounded_ = true;
		}
	}
}

bool ColliderComponent::isGrounded()
{
	return grounded_;
}

bool ColliderComponent::isColliding()
{
	return colliding_;
}

void ColliderComponent::receive(ComponentMessage message)
{

}

void ColliderComponent::update(float deltaTime, float *playerXY, int numPlayers)
{

}

float ColliderComponent::getLocalX() { return x_; }
float ColliderComponent::getLocalY() { return y_; }
void ColliderComponent::setX(float x) { x_ = x; }
void ColliderComponent::setY(float y) { y_ = y; }

float ColliderComponent::getWidth() { return width_; }
float ColliderComponent::getHeight() { return height_; }

void ColliderComponent::setWidth(float width) { width_ = width; }
void ColliderComponent::setHeight(float height) { height_ = height; }

float ColliderComponent::getMinX()
{
	float result = entity_->getX() + x_;
	return result;
}

float ColliderComponent::getMaxX()
{
	float result = entity_->getX() + x_ + width_;
	return result;
}

float ColliderComponent::getMinY()
{
	float result = entity_->getY() + y_;
	return result;
}

float ColliderComponent::getMaxY()
{
	float result = entity_->getY() + y_ + height_;
	return result;
}

ColliderCategory ColliderComponent::getCategory() { return category_; }
void ColliderComponent::setCategory(ColliderCategory Category) { category_ = Category; }