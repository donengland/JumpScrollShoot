//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_TRANSFORM_COMPONENT_H_GUARD
#define __JSS_TRANSFORM_COMPONENT_H_GUARD

#include "JSS_Component.h"

class TransformComponent : public Component
{
public:
	TransformComponent() { x = 0.0f; y = 0.0f; }
	TransformComponent(float X, float Y) { x = X; y = Y; }

	void receive(ComponentMessage message);

	void setX(float X) { x = X; }
	void setY(float Y) { y = Y; }

	float getX() { return x; }
	float getY() { return y; }

	void changeX(float deltaX) { x += deltaX; }
	void changeY(float deltaY) { y += deltaY; }

private:
	float x, y;
};
#endif