//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <iostream>
#include <cmath>
#include "JSS_GraphicsComponent.h"


GraphicsComponent::GraphicsComponent()
{
	entity_ = nullptr;
  active_ = false;
};

GraphicsComponent::GraphicsComponent(Entity *entity, int id,
									 uint8 red, uint8 green, uint8 blue, uint8 alpha,
									 float width, float height,
									 float localX, float localY)
{
	entity_ = entity;
	id_ = id;
  active_ = true;

	x_ = localX;
	y_ = localY;

	w_ = width;
	h_ = height;

	red_ = red;
	green_ = green;
	blue_ = blue;
	alpha_ = alpha;
};

void GraphicsComponent::setEntity(Entity *entity)
{
	entity_ = entity;
	entity_->setGraphics(this, id_);
};

void GraphicsComponent::setId(int id)
{
	id_ = id;
	entity_->setGraphicsId(id);
}
int GraphicsComponent::getId() { return id_; }

bool GraphicsComponent::get_active() { return active_; }
void GraphicsComponent::set_active(bool active) { active_ = active; }

void GraphicsComponent::render(SDL_Renderer *renderer, int xOffset, int yOffset)
{
	SDL_Rect transformRect = { (int)(getMinX() - xOffset), (int)(getMinY() - yOffset), (int)w_, (int)h_ };
	SDL_SetRenderDrawColor(renderer, red_, green_, blue_, alpha_);
	SDL_RenderFillRect(renderer, &transformRect);
};

void GraphicsComponent::setColor(uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
	red_ = red;
	green_ = green;
	blue_ = blue;
	alpha_ = alpha;
}

void GraphicsComponent::receive(ComponentMessage message)
{

};

void GraphicsComponent::update(float deltaTime, float *playerXY, int numPlayers)
{

}

float GraphicsComponent::getLocalX() { return x_; }
float GraphicsComponent::getLocalY() { return y_; }
void GraphicsComponent::setX(float x) { x_ = x; }
void GraphicsComponent::setY(float y) { y_ = y; }

float GraphicsComponent::getWidth() { return w_; }
float GraphicsComponent::getHeight() { return h_; }

void GraphicsComponent::setWidth(float width) { w_ = width; }
void GraphicsComponent::setHeight(float height) { h_ = height; }

float GraphicsComponent::getMinX()
{
	float result = entity_->getX() + x_;
	return result;
};
float GraphicsComponent::getMaxX()
{
	float result = entity_->getX() + x_ + w_;
	return result;
};

float GraphicsComponent::getMinY()
{
	float result = entity_->getY() + y_;
	return result;
};
float GraphicsComponent::getMaxY()
{
	float result = entity_->getY() + y_ + h_;
	return result;
};