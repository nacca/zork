#include "Entity.h"

class Player: public Entity
{
private:
	list<Item*> listOfInventory;

public:
	Player();
	Player(Place* actualPlace);
	~Player();

	Place* getActualPlace();
	void setActualPlace(Place* actualPlace);

	void addItem(Item* item);
	void removeItem(Item* item);
	bool isItemInTheInventory(string itemName);

	void readInventory();
	void readItem(string itemName);

};

