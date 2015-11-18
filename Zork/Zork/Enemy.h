#pragma once

#include "Entity.h"

class Enemy : public Entity
{
private:
	Item* itemEquiped;
public:
	Enemy();
	Enemy(Item* itemEquiped);
	~Enemy();

	Item* getItemEquiped() const;
	void setItemEquiped(Item* itemEquiped);
};

