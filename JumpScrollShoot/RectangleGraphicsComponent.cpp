//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <stdint.h>
#include <SDL.h>
#include "Entity.h"
#include "RectangleGraphicsComponent.h"

namespace don_entity_component
{
  RectangleGraphicsComponent::RectangleGraphicsComponent(SDL_Renderer *renderer) { renderer_ = renderer; }
  void RectangleGraphicsComponent::Start() {}
  void RectangleGraphicsComponent::Stop() {}
  void RectangleGraphicsComponent::Update(Entity &entity, float deltaTime)
  {
    SDL_Rect transformRect = { (int)(entity.x_position() - kHalfSize),
                               (int)(entity.y_position() - kHalfSize),
                               (kHalfSize * 2), (kHalfSize * 2) };
    SDL_SetRenderDrawColor(renderer_, 0xAA, 0x55, 0x55, 0xFF);
    SDL_RenderFillRect(renderer_, &transformRect);
  }
  void RectangleGraphicsComponent::Receive(DEC_Message message) {}
}