#include "place.h"

Place::Place()
{
	name = "uknown";
	story = "";
	enemyPresent = false;
	enemyInThePlace = NULL;
}

Place::Place(string name)
{
	this->name = name;
	story = "";
	enemyPresent = false;
	enemyInThePlace = NULL;
}

Place::Place(string name, string story)
{
	this->name = name;
	this->story = story;
	enemyPresent = false;
	enemyInThePlace = NULL;
}

Place::Place(string name, string story, bool enemyPresent, Enemy* enemyInThePlace)
{
	this->name = name;
	this->story = story;
	this->enemyPresent = enemyPresent;
	this->enemyInThePlace = enemyInThePlace;
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
	cout << "<-- " << story << endl;
	for (int i = 0; i < directions.size(); ++i)
	{
		if(directions[i].direction == "up" || directions[i].direction == "down")
			cout << "<-- You can see " << directions[i].definition << " going " << directions[i].direction << ". ";
		else
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
	if (enemyPresent)
	{
		cout << "<-- CAUTION: Theres also a enemy in the room!!!" << endl;
		if (enemyInThePlace->getItemEquiped()->getName() == "knife") 
		{
			cout << "<-- Care, he has a knife!" << endl;
		}
		if (enemyInThePlace->getItemEquiped()->getName() == "gun")
		{
			cout << "<-- He has a gun, and it's pointing to you!!! RUN, do something!!!" << endl;
		}
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

void Place::addEnemy(Enemy* enemy)
{
	enemyPresent = true;
	enemyInThePlace = enemy;
}

void Place::enemyDies()
{
	listOfItemsInPlace.push_back(enemyInThePlace->getItemEquiped());
	enemyPresent = false;
	enemyInThePlace = NULL;
}

bool Place::isEnemyPresent()
{
	return enemyPresent;
}

Enemy* Place::getEnemy()
{
	return enemyInThePlace;
}

Item* Place::getItemByName(string itemName)
{
	for (std::list<Item*>::iterator it = listOfItemsInPlace.begin(); it != listOfItemsInPlace.end(); ++it)
	{
		if ((*it)->getName() == itemName)
			return (*it);
	}
}