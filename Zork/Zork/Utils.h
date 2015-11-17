#pragma once
#include <iostream>
#include "Item.h"
#include <time.h>
#include <stdlib.h> 

enum class InputOrder { GO, TAKE, DROP, INVENTORY, EXIT, WATCH, READ, OPEN, EQUIP, UNEQUIP, ATTACK, THROW, UNKNOWN };

class Utils
{
public:
	Utils();
	~Utils();
	bool playerWinsOrLoses(string action, Item* playerItem, Item* enemyItem, clock_t timeSinceEnterRoom);
	InputOrder selectEnum(string s);

};

