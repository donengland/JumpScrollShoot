#ifndef JUMP_SCROLL_SHOOT_ENTITY_H
#define JUMP_SCROLL_SHOOT_ENTITY_H
//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <stdint.h>
#include <vector>
#include <memory>
#include "BaseComponent.h"

namespace don_entity_component
{
  class Entity
  {
  public:
    Entity();
    // TODO(don): update to take a param for type of system component
    void AddComponent(std::unique_ptr<BaseComponent> component);
    void Update(float delta_time);
    void Receive(DEC_Message message);

    float x_position();
    float y_position();
    void set_x_position(float x_position);
    void set_y_position(float y_position);
  private:
    float x_position_, y_position_;
    float x_velocity_, y_velocity_;
    // TODO(don): update state to hold pointers to system specific components
    std::vector<std::unique_ptr<BaseComponent>> components_;
  };
}
#endif // JUMP_SCROLL_SHOOT_ENTITY_H