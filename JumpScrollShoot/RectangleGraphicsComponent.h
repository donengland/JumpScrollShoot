#ifndef JUMP_SCROLL_SHOOT_RECTANGLE_GRAPHICS_COMPONENT_H
#define JUMP_SCROLL_SHOOT_RECTANGLE_GRAPHICS_COMPONENT_H
//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <stdint.h>
#include <SDL.h>
#include "GraphicsComponent.h"

namespace don_entity_component
{
  class RectangleGraphicsComponent : public GraphicsComponent
  {
  public:
    RectangleGraphicsComponent(SDL_Renderer *renderer);
    void Start();
    void Stop();
    void Update(Entity &entity, float deltaTime);
    void Receive(DEC_Message message);
  private:
    SDL_Renderer *renderer_;
    const int kHalfSize = 25;
  };
}
#endif // JUMP_SCROLL_SHOOT_RECTANGLE_GRAPHICS_COMPONENT_H