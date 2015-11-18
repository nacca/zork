#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Enemy.h"
using namespace std;


class Place
{
private:
	struct Door {
		string direction;
		string definition;
		Place* nextRoom;
		bool opened;
		string itemToOpen;
	};
	string name;
	string story;
	vector<Door> directions;
	list<Item*> listOfItemsInPlace;
	bool enemyPresent;
	Enemy* enemyInThePlace;

public:

	// Creadores

	Place();
	Place(string name);
	Place(string name, string story);
	Place(string name, string story, bool enemyPresent, Enemy* enemyInThePlace);
	~Place();

	// Consultores

	string getName() const;
	bool isItemPresent(string itemName) const;
	bool isEnemyPresent() const;
	Enemy* getEnemy() const;
	void readPlace() const;
	Item* getItemByName(string itemName) const;

	// Modificadores

	void enemyDies();
	void setDirection(string direction, string definition, Place* nextRoom, bool opened, string itemToOpen);
	void addItem(Item* item);
	void addEnemy(Enemy* enemy);
	void removeItem(Item* item);
	Place* goTo(string direction);

};

