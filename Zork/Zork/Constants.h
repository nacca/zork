#pragma once
#include <iostream>
#include <string>
#include "Item.h"
#include <time.h>
#include <stdlib.h> 

class Constants
{
public:
	Constants();
	~Constants();
	const bool playerWinsOrLoses(string action, Item* playerItem, Item* enemyItem, clock_t timeSinceEnterRoom);
};

