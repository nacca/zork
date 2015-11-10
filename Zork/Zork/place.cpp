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
	cout << "Estas a " << name << endl;
	cout << "En aquesta habitacio hi ha : " << endl;
	if (northPlace != NULL)
		cout << "Una habitacio cap el north" << endl;
	if (southPlace != NULL)
		cout << "Una habitacio cap el south" << endl;
	if (westPlace != NULL)
		cout << "Una habitacio cap el west" << endl;
	if (eastPlace != NULL)
		cout << "Una habitacio cap el east" << endl;
	if (upPlace != NULL)
		cout << "Una habitacio cap el up" << endl;
	if (downPlace != NULL)
		cout << "Una habitacio cap el down" << endl;
	cout << endl;
}

