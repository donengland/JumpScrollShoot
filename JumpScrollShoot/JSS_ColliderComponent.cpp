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
	entity = nullptr;
};

ColliderComponent::ColliderComponent(Entity *ColliderEntity,
									 float localX, float localY,
									 float Width, float Height,
									 ColliderCategory Category)
{
	entity = ColliderEntity;
	category = Category;

	x = localX;
	y = localY;

	width = Width;
	height = Height;

	right = false;
	left = false;
	above = false;
	below = false;
	grounded = false;
	colliding = false;
	dead = false;
};

void ColliderComponent::setEntity(Entity *ColliderEntity)
{
	entity = ColliderEntity;
}

void ColliderComponent::resetCollisions()
{
	right = false;
	left = false;
	above = false;
	below = false;
	grounded = false;
	colliding = false;
};

void ColliderComponent::resolveCollision(ColliderComponent &other)
{
	// We had a collision with another Collider
	colliding = true;
	
	if ((category == ColliderCategory::playerAttack) && (other.category == ColliderCategory::immobile))
	{
		//std::cout << "Collider Component:Sending DeleteMe Message" << std::endl;
		if (!dead)
		{
			ComponentMessage msg;
			msg.type = MessageType::DeleteMe;
			msg.key = MessageKey::Damage;
			msg.value = 0.f;
			entity->broadcast(msg);
			dead = true;
		}
	}
	else if (other.category == ColliderCategory::immobile)
	{
		// Flag for possibly being completely inside the other collider
		bool inside = false;
		float changeX = 100000.0f;
		float changeY = 100000.0f;
		if (getMaxX() > other.getMaxX())
		{
			// Other to my left
			left = true;
			changeX = (other.getMaxX() - getMinX());
		}
		else if (getMinX() < other.getMinX())
		{
			// Other to my right
			right = true;
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
			above = true;
			changeY = (other.getMaxY() - getMinY());
		}
		else if (getMinY() < other.getMinY())
		{
			// Consider other below me
			below = true;
			changeY = (other.getMinY() - getMaxY());
		}
		else
		{
			if (inside)
			{
				inside = false;
				left = true;
				right = true;
				above = true;
				below = true;
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
			entity->changeX(changeX);
		}
		else
		{
			entity->changeY(changeY);
		}

		if (below && (abs(getMaxY() - other.getMinY()) < .5f))
		{
			grounded = true;
		}
	}
};

bool ColliderComponent::isGrounded()
{
	return grounded;
};

bool ColliderComponent::isColliding()
{
	return colliding;
};

void ColliderComponent::receive(ComponentMessage message)
{

};

void ColliderComponent::update(float deltaTime)
{

};

float ColliderComponent::getLocalX() { return x; }
float ColliderComponent::getLocalY() { return y; }
void ColliderComponent::setX(float X) { x = X; }
void ColliderComponent::setY(float Y) { y = Y; }

float ColliderComponent::getWidth() { return width; }
float ColliderComponent::getHeight() { return height; }

void ColliderComponent::setWidth(float Width) { width = Width; }
void ColliderComponent::setHeight(float Height) { height = Height; }

float ColliderComponent::getMinX()
{
	float result = entity->getX() + x;
	return result;
};
float ColliderComponent::getMaxX()
{
	float result = entity->getX() + x + width;
	return result;
};

float ColliderComponent::getMinY()
{
	float result = entity->getY() + y;
	return result;
};
float ColliderComponent::getMaxY()
{
	float result = entity->getY() + y + height;
	return result;
};

ColliderCategory ColliderComponent::getCategory() { return category; }
void ColliderComponent::setCategory(ColliderCategory Category) { category = Category; }