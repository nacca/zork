#pragma once

#include "Entity.h"
#include "Place.h"

class Player: public Entity
{
private:
	list<Item*> listOfInventory;
	Place* actualPlace;

public:
	Player();
	Player(Place* actualPlace);
	~Player();

	Place* getActualPlace();
	void setActualPlace(Place* actualPlace);

	void addItem(Item* item);
	void removeItem(Item* item);
	bool isItemInTheInventory(string itemName);
	void equipItem(string itemName);
	void unequipItem();
	Item* getItemEquiped();

	void readInventory();
	void readItem(string itemName);

};

