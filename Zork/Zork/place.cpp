#include "place.h"

Place::Place()
{
	name = "uknown";
	story = "";
}

Place::Place(string name)
{
	this->name = name;
	story = "";
}

Place::Place(string name, string story)
{
	this->name = name;
	this->story = story;
}

Place::~Place()
{
}

string Place::getName()
{
	return name;
}

void Place::setDirection(string direction, string definition, Place* nextRoom, bool opened, string itemToOpen)
{
	Door door = { direction, definition, nextRoom, opened, itemToOpen };
	directions.push_back(door);
}

Place* Place::goTo(string direction)
{
	for (int i = 0; i < directions.size(); ++i)
	{
		if (direction == directions[i].direction)
		{
			return directions[i].nextRoom;
		}
	}
	return NULL;
}

void Place::readPlace()
{
	cout << "<-- You're in a " << name << ". " << story << endl;
	for (int i = 0; i < directions.size(); ++i)
	{
		cout << "<-- At the " << directions[i].direction << " you can see " << directions[i].definition << ". ";
		if (!directions[i].opened)
			cout << "It seems that the door is closed.";
		cout << endl;
	}
	if (!listOfItemsInPlace.empty())
	{
		cout << "<-- You can see: " << endl;
		for (std::list<Item*>::iterator it = listOfItemsInPlace.begin(); it != listOfItemsInPlace.end(); ++it)
		{
			cout << "<-- A " << (*it)->getName() << endl;
		}
		cout << endl;
	}
}

void Place::addItem(Item* item)
{
	listOfItemsInPlace.push_back(item);
}

void Place::removeItem(Item* item)
{
	listOfItemsInPlace.remove(item);
}

bool Place::isItemPresent(string itemName)
{
	for (std::list<Item*>::iterator it = listOfItemsInPlace.begin(); it != listOfItemsInPlace.end(); ++it)
	{
		if((*it)->getName() == itemName)
			return true;
	}
	return false;
}
