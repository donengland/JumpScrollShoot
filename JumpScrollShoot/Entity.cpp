//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <stdint.h>
#include <vector>
#include "Entity.h"

namespace don_entity_component
{
  Entity::Entity()
  {

  }
  void Entity::AddComponent(std::unique_ptr<BaseComponent> component)
  {
    components_.emplace_back(std::move(component));
  }
  void Entity::Update(float delta_time)
  {
    for (auto &component : components_)
    {
      component->Update(*this, delta_time);
    }
  }
  void Entity::Receive(DEC_Message message)
  {

  }
  float Entity::x_position() { return x_position_; }
  float Entity::y_position() { return y_position_; }
  void Entity::set_x_position(float x_position) { x_position_ = x_position; }
  void Entity::set_y_position(float y_position) { y_position_ = y_position; }
}