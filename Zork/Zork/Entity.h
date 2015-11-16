#pragma once

#include "Item.h"

class Entity
{
protected:
	Item* equipedItem;

public:
	Entity();
	Entity(Item* equipedItem);
	virtual ~Entity();

};

