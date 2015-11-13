#include "place.h"

Place::Place()
{
	northPlace = NULL;
	southPlace = NULL;
	westPlace = NULL;
	eastPlace = NULL;
	upPlace = NULL;
	downPlace = NULL;
}

Place::Place(string name)
{
	this->name = name;
	northPlace = NULL;
	southPlace = NULL;
	westPlace = NULL;
	eastPlace = NULL;
	upPlace = NULL;
	downPlace = NULL;
}

Place::~Place()
{
}

string Place::getName()
{
	return name;
}

Place* Place::getNorthPlace()
{
	return northPlace;
}

Place* Place::getSouthPlace()
{
	return southPlace;
}

Place* Place::getWestPlace()
{
	return westPlace;
}

Place* Place::getEastPlace()
{
	return eastPlace;
}

Place* Place::getUpPlace()
{
	return upPlace;
}

Place* Place::getDownPlace()
{
	return downPlace;
}

void Place::setNorthPlace(Place* northPlace)
{
	this->northPlace = northPlace;
}

void Place::setSouthPlace(Place* southPlace)
{
	this->southPlace = southPlace;
}

void Place::setWestPlace(Place* westPlace)
{
	this->westPlace = westPlace;
}

void Place::setEastPlace(Place* eastPlace)
{
	this->eastPlace = eastPlace;
}

void Place::setUpPlace(Place* upPlace)
{
	this->upPlace = upPlace;
}

void Place::setDownPlace(Place* downPlace)
{
	this->downPlace = downPlace;
}

void Place::readPlace()
{
	cout << "<-- You're in " << name << endl;
	cout << "<-- In this place you can see : " << endl;
	if (northPlace != NULL)
		cout << "<-- A place to the north" << endl;
	if (southPlace != NULL)
		cout << "<-- A place to the south" << endl;
	if (westPlace != NULL)
		cout << "<-- A place to the west" << endl;
	if (eastPlace != NULL)
		cout << "<-- A place to the east" << endl;
	if (upPlace != NULL)
		cout << "<-- A place to the up" << endl;
	if (downPlace != NULL)
		cout << "<-- A place to the down" << endl;
	for (std::list<Item*>::iterator it = listOfItemsInPlace.begin(); it != listOfItemsInPlace.end(); ++it)
	{
		cout << "<-- A/An: " << (*it)->getName() << endl;
	}   	
	cout << endl;
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
