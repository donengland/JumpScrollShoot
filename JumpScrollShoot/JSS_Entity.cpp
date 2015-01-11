//============================================================================
// Name        : 
// Author      : Don England
// Version     : 
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include "JSS_Entity.h"

void Entity::broadcast(ComponentMessage message)
{
	for (auto &i : myComponents)
	{
		i->receive(message);
	}
};

void Entity::addComponent(Component *c)
{
	myComponents.push_back(c);
};

void Entity::removeComponent(Component *c)
{
	myComponents.erase(std::remove(myComponents.begin(),
								   myComponents.end(),
								   c),
					   myComponents.end());
};