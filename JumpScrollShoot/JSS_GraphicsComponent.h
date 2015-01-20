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
	GraphicsComponent(Entity *entity, int id,
					  uint8 red = 0x00, uint8 green = 0x00, uint8 blue = 0x00, uint8 alpha = 0xFF,
					  float width = 0.0f, float height = 0.0f,
					  float localX = 0.0f, float localY = 0.0f);

	void setEntity(Entity *entity);

	void receive(ComponentMessage message);
	void update(float deltaTime, float *playerXY, int numPlayers);

	void render(SDL_Renderer *renderer, int xOffset, int yOffset);

	void setColor(uint8 red, uint8 green, uint8 blue, uint8 alpha = 0xFF);

  bool get_active();
  void set_active(bool active);

	float getLocalX();
	float getLocalY();

	float getMinX();
	float getMaxX();

	float getMinY();
	float getMaxY();

	void setX(float x);
	void setY(float x);

	void setId(int id);
	int getId();

	float getWidth();
	float getHeight();

	void setWidth(float width);
	void setHeight(float height);

private:
	Entity *entity_;
  bool active_;
	int id_;

	float x_, y_;

	float w_, h_;

	uint8 red_, green_, blue_, alpha_;
};

#endif