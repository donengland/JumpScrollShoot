#ifndef JUMP_SCROLL_SHOOT_PHYSICS_COMPONENT_H
#define JUMP_SCROLL_SHOOT_PHYSICS_COMPONENT_H
//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <stdint.h>
#include "BaseComponent.h"

namespace don_entity_component
{
  class PhysicsComponent : public BaseComponent
  {
  public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Update(Entity &entity, float deltaTime) = 0;
    virtual void Receive(DEC_Message message) = 0;
  };
}
#endif // JUMP_SCROLL_SHOOT_PHYSICS_COMPONENT_H