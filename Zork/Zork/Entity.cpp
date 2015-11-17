#include "Entity.h"

Entity::Entity()
{
	equipedItem = NULL;
}

Entity::Entity(Item* equipedItem)
{
	this->equipedItem = equipedItem;
}

Entity::~Entity()
{
}