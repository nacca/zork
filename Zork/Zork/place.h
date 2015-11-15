#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Item.h"
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

public:
	Place();
	Place(string name);
	Place(string name, string story);
	~Place();

	string getName();

	void setDirection(string direction, string definition, Place* nextRoom, bool opened, string itemToOpen);

	void addItem(Item* item);
	void removeItem(Item* item);
	bool isItemPresent(string itemName);
	Place* goTo(string direction);

	void readPlace();

};

