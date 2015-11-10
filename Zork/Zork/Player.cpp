#include "Player.h"



Player::Player()
{
}

Player::Player(Place* actualPlace)
{
	this->actualPlace = actualPlace;
}


Player::~Player()
{
}

Place* Player::getActualPlace()
{
	return actualPlace;
}

void Player::setActualPlace(Place* actualPlace)
{
	this->actualPlace = actualPlace;
}

void Player::addItem(Item* item)
{
	listOfInventory.push_back(item);
}

void Player::removeItem(Item* item)
{
	listOfInventory.remove(item);
}

void Player::readInventory()
{
	if (listOfInventory.size() == 0)
		cout << "The player doesn't have any item in the inventory" << endl;
	else
	{
		cout << "The player have in the inventory:" << endl;
		for (std::list<Item*>::iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
		{
			cout << (*it)->getName() << endl;
		}
	}
}

bool Player::isItemInTheInventory(string itemName)
{
	for (std::list<Item*>::iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
	{
		if ((*it)->getName() == itemName)
			return true;
	}
	return false;
}
