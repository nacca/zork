#include "Item.h"

Item::Item()
{
}

Item::Item(string name, string message, bool canTakeIt)
{
	this->name = name;
	this->message = message;
	this->canTakeIt = canTakeIt;
	canBeOpened = false;
	itemInside = NULL;
	needCode = false;
	code = "";
}

Item::Item(string name, string message, bool canTakeIt, bool canBeOpened, Item* itemInside)
{
	this->name = name;
	this->message = message;
	this->canTakeIt = canTakeIt;
	this->canBeOpened = canBeOpened;
	this->itemInside = itemInside;
	needCode = false;
	code = "";
}

Item::Item(string name, string message, bool canTakeIt, bool canBeOpened, Item* itemInside, bool needCode, string code)
{
	this->name = name;
	this->message = message;
	this->canTakeIt = canTakeIt;
	this->canBeOpened = canBeOpened;
	this->itemInside = itemInside;
	this->needCode = needCode;
	this->code = code;
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

string Item::readIt()
{
	return message;
}

void Item::setCanTakeIt(bool canTakeIt)
{
	this->canTakeIt = canTakeIt;
}

bool Item::youCanOpenIt()
{
	return canBeOpened;
}

Item* Item::getItemInside()
{
	return itemInside;
}

bool Item::needCodeToOpen()
{
	return needCode;
}

bool Item::checkCode(string code)
{
	return this->code == code;
}

string Item::getMessage()
{
	return message;
}