#include "Item.h"

Item::Item()
{
}

Item::Item(string name, bool canTakeIt)
{
	this->name = name;
	this->canTakeIt = canTakeIt;
}

Item::~Item()
{
}

string Item::getName()
{
	return name;
}

void Item::setName(string name)
{
	this->name = name;
}

bool Item::youCanTakeIt() 
{
	return canTakeIt;
}

void Item::setCanTakeIt(bool canTakeIt)
{
	this->canTakeIt = canTakeIt;
}
