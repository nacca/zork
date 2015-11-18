#pragma once

#include "Entity.h"
#include "Place.h"

class Player : public Entity
{
private:
	list<Item*> listOfInventory;
	Place* actualPlace;

public:

	// Creadores
	Player();
	Player(Place* actualPlace);
	~Player();

	// Consultores

	Place* getActualPlace() const;
	bool isItemInTheInventory(string itemName) const;
	Item* getItemEquiped() const;
	Item* getItemByName(string itemName) const;
	void readItem(string itemName) const;
	void readInventory() const;

	// Modificadores

	void setActualPlace(Place* actualPlace);
	void addItem(Item* item);
	void removeItem(Item* item);
	void equipItem(string itemName);
	void unequipItem();

};

