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
	Place();
	Place(string name);
	Place(string name, string story);
	Place(string name, string story, bool enemyPresent, Enemy* enemyInThePlace);
	~Place();

	string getName();

	void setDirection(string direction, string definition, Place* nextRoom, bool opened, string itemToOpen);

	void addItem(Item* item);
	void addEnemy(Enemy* enemy);
	void removeItem(Item* item);
	bool isItemPresent(string itemName);
	Place* goTo(string direction);

	void enemyDies();
	bool isEnemyPresent();
	Enemy* getEnemy();
	void readPlace();

};

