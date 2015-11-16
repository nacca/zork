#pragma once

#include "Entity.h"

class Enemy: public Entity
{
private:
	Item* itemEquiped;
public:
	Enemy();
	Enemy(Item* itemEquiped);
	~Enemy();

	Item* getItemEquiped();
	void setItemEquiped(Item* itemEquiped);
	Item* Die();

};

