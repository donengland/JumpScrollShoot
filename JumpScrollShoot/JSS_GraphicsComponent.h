//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef JSS_GRAPHICS_COMPONENT_H_GUARD
#define JSS_GRAPHICS_COMPONENT_H_GUARD

#include <sdl.h>
#include "JSS_Entity.h"

typedef uint8_t uint8;

// TODO(don): consider "pre-computing" min?, max?, etc.
//    Trades memory for speed, need profiling first
//    Perhaps store min max instead of min + width/height
class GraphicsComponent : public Component
{
public:
	GraphicsComponent();
	GraphicsComponent(Entity *GraphicsEntity,
					  uint8 Red = 0x00, uint8 Green = 0x00, uint8 Blue = 0x00, uint8 Alpha = 0xFF,
					  float Width = 0.0f, float Height = 0.0f,
					  float localX = 0.0f, float localY = 0.0f);

	void receive(ComponentMessage message);

	void render(SDL_Renderer *renderer, int xOffset, int yOffset);

	void setColor(uint8 Red, uint8 Green, uint8 Blue, uint8 Alpha = 0xFF);

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

private:
	Entity *entity;

	float x, y;

	float width, height;

	uint8 red, green, blue, alpha;
};

#endif