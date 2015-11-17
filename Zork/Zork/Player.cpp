#include "Player.h"

Player::Player()
{
	equipedItem = NULL;
}

Player::Player(Place* actualPlace)
{
	this->actualPlace = actualPlace;
	equipedItem = NULL;
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
		cout << "<-- The player doesn't have any item in the inventory" << endl;
	else
	{
		cout << "<--- The player have in the inventory:" << endl;
		for (std::list<Item*>::iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
		{
			cout << "<-- " << (*it)->getName() << endl;
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

void Player::readItem(string itemName)
{
	for (std::list<Item*>::iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
	{
		if ((*it)->getName() == itemName)
		{
			cout << "<-- " << (*it)->readIt() << endl;
			return;
		}		
	}
	cout << "<-- You don't have this item in the inventory." << endl;
}


void Player::equipItem(string itemName)
{
	if (itemName != "gun" && itemName != "knife") cout << "<-- This item can't be equiped" << endl;
	else {
		for (std::list<Item*>::iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
		{
			if ((*it)->getName() == itemName)
			{
				equipedItem = (*it);
				cout << "<-- You have equiped a " << itemName << "." << endl;
				return;
			}
		}
		cout << "<-- You don't have this item in the inventory." << endl;
	}
}

void Player::unequipItem()
{
	if (equipedItem == NULL)
		cout << "<-- You don't have nothing equiped." << endl;
	else
	{
		cout << "<-- " << equipedItem->getName() << " unequiped." << endl;
		equipedItem = NULL;
	}
}

Item* Player::getItemEquiped()
{
	return equipedItem;
}

Item* Player::getItemByName(string itemName)
{
	for (std::list<Item*>::iterator it = listOfInventory.begin(); it != listOfInventory.end(); ++it)
	{
		if ((*it)->getName() == itemName)
			return (*it);
	}
}