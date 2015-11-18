#include "Item.h"

Item::Item()
{
	name = "",
	message = "";
	canTakeIt = false;
	canBeOpened = false;
	needCode = false;
	code = "";
	theresAnItemInside = false;
	itemInside = NULL;
	insideAnItem = false;
	outsideItem = NULL;
	opened = false;
}

Item::Item(string name, string message, bool canTakeIt)
{
	this->name = name,
	this->message = message;
	this->canTakeIt = canTakeIt;
	canBeOpened = false;
	needCode = false;
	code = "";
	theresAnItemInside = false;
	itemInside = NULL;
	insideAnItem = false;
	outsideItem = NULL;
	opened = false;
}

Item::Item(string name, string message, bool canTakeIt, bool canBeOpened, bool opened, bool theresAnItemInside, Item* itemInside, bool needCode, string code)
{
	this->name = name,
	this->message = message;
	this->canTakeIt = canTakeIt;
	this->canBeOpened = canBeOpened;
	this->opened = opened;
	this->theresAnItemInside = theresAnItemInside;
	this->itemInside = itemInside;
	this->needCode = needCode;
	this->code = code;
	insideAnItem = false;
	outsideItem = NULL;
}

Item::Item(string name, string message, bool canTakeIt, bool insideAnItem, Item* outsideItem)
{
	this->name = name,
	this->message = message;
	this->canTakeIt = canTakeIt;
	this->insideAnItem = insideAnItem;
	this->outsideItem = outsideItem;
	code = "";
	canBeOpened = false;
	needCode = false;
	itemInside = NULL;
	theresAnItemInside = true;
	opened = false;
}

Item::~Item()
{
}

string Item::getName() const
{
	return name;
}

bool Item::youCanTakeIt() const
{
	return canTakeIt;
}

string Item::readIt() const
{
	return message;
}

bool Item::youCanOpenIt() const
{
	return canBeOpened;
}

Item* Item::getItemInside() const
{
	return itemInside;
}

bool Item::needCodeToOpen() const
{
	return needCode;
}

bool Item::checkCode(string code) const
{
	return this->code == code;
}

string Item::getMessage() const
{
	return message;
}

Item* Item::takeItem()
{
	Item* aux = itemInside;
	itemInside = NULL;
	theresAnItemInside = false;
	return aux;
}

bool Item::haveAnItemInside() const
{
	return theresAnItemInside;
}

void Item::putItem(Item* newItemInside)
{
	theresAnItemInside = true;
	itemInside = newItemInside;
}

void Item::putInsideOfAnItem(Item* newOutSideItem)
{
	insideAnItem = true;
	outsideItem = newOutSideItem;
}

bool Item::isInsideAnItem() const
{
	return insideAnItem;
}

Item* Item::takeOutsideItem()
{
	Item* aux = outsideItem;
	outsideItem = NULL;
	insideAnItem = false;
	return aux;
}

Item* Item::getItemOutside() const
{
	return outsideItem;
}

bool Item::isOpened() const
{
	return opened;
}

void Item::open()
{
	opened = true;
}

void Item::close()
{
	opened = false;
}