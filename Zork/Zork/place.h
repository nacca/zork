#include <iostream>
#include <string>
#include <list>
#include "Item.h"
using namespace std;

class Place
{
private:
	string name;
	Place* northPlace;
	Place* southPlace;
	Place* westPlace;
	Place* eastPlace;
	Place* upPlace;
	Place* downPlace;
	list<Item*> listOfItemsInPlace;

public:
	Place();
	Place(string name);
	~Place();

	string getName();
	Place* getNorthPlace();
	Place* getSouthPlace();
	Place* getWestPlace();
	Place* getEastPlace();
	Place* getUpPlace();
	Place* getDownPlace();

	void setNorthPlace(Place* northPlace);
	void setSouthPlace(Place* southPlace);
	void setWestPlace(Place* westPlace);
	void setEastPlace(Place* eastPlace);
	void setUpPlace(Place* upPlace);
	void setDownPlace(Place* downPlace);

	void addItem(Item* item);
	void removeItem(Item* item);
	bool isItemPresent(string itemName);

	void readPlace();

};

