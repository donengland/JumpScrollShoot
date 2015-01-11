//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#ifndef __JSS_ENTITY_H_GUARD
#define __JSS_ENTITY_H_GUARD

#include <vector>
#include <algorithm>

#include "JSS_Component.h"

// NOTE(don): Entity contains pointers to components that hold it's state.
class Entity
{
public:
	void broadcast(ComponentMessage message);
	void addComponent(Component *c);
	void removeComponent(Component *c);
private:
	std::vector<Component*> myComponents;
};

#endif