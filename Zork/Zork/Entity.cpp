#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(Item* equipedItem)
{
	this->equipedItem = equipedItem;
}

Entity::~Entity()
{
}