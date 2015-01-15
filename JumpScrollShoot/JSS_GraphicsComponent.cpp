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
	entity = nullptr;
};

GraphicsComponent::GraphicsComponent(Entity *GraphicsEntity,
									 uint8 Red, uint8 Green, uint8 Blue, uint8 Alpha,
									 float Width, float Height,
									 float localX, float localY)
{
	entity = GraphicsEntity;

	x = localX;
	y = localY;

	width = Width;
	height = Height;

	red = Red;
	green = Green;
	blue = Blue;
	alpha = Alpha;
};

void GraphicsComponent::setEntity(Entity *GraphicsEntity)
{
	entity = GraphicsEntity;
};

void GraphicsComponent::render(SDL_Renderer *renderer, int xOffset, int yOffset)
{
	SDL_Rect transformRect = { (int)(getMinX() - xOffset), (int)(getMinY() - yOffset), (int)width, (int)height };
	SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
	SDL_RenderFillRect(renderer, &transformRect);
};

void GraphicsComponent::setColor(uint8 Red, uint8 Green, uint8 Blue, uint8 Alpha)
{
	red = Red;
	green = Green;
	blue = Blue;
	alpha = Alpha;
}

void GraphicsComponent::receive(ComponentMessage message)
{

};

void GraphicsComponent::update(float deltaTime)
{

}

float GraphicsComponent::getLocalX() { return x; }
float GraphicsComponent::getLocalY() { return y; }
void GraphicsComponent::setX(float X) { x = X; }
void GraphicsComponent::setY(float Y) { y = Y; }

float GraphicsComponent::getWidth() { return width; }
float GraphicsComponent::getHeight() { return height; }

void GraphicsComponent::setWidth(float Width) { width = Width; }
void GraphicsComponent::setHeight(float Height) { height = Height; }

float GraphicsComponent::getMinX()
{
	float result = entity->getX() + x;
	return result;
};
float GraphicsComponent::getMaxX()
{
	float result = entity->getX() + x + width;
	return result;
};

float GraphicsComponent::getMinY()
{
	float result = entity->getY() + y;
	return result;
};
float GraphicsComponent::getMaxY()
{
	float result = entity->getY() + y + height;
	return result;
};