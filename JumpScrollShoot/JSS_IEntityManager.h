//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_I_ENTITY_MANAGER_H_GUARD
#define __JSS_I_ENTITY_MANAGER_H_GUARD

// TODO(don): there must be a better way to do this
class Entity;
class GraphicsComponent;
class ColliderComponent;
class PhysicsComponent;
class InputComponent;

class IEntityManager
{
public:
	~IEntityManager() {}
	virtual bool instantiate(Entity *e, GraphicsComponent *g = nullptr, ColliderComponent *c = nullptr, PhysicsComponent *p = nullptr, InputComponent *i = nullptr) = 0;
	virtual void deleteEntity(int id) = 0;
};

#endif