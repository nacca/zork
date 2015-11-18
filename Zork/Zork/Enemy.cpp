#include "Enemy.h"

Enemy::Enemy()
{
	equipedItem = NULL;
}

Enemy::Enemy(Item* itemEquiped)
{
	this->itemEquiped = itemEquiped;
}

Enemy::~Enemy()
{
}

Item* Enemy::getItemEquiped() const
{
	return itemEquiped;
}

void Enemy::setItemEquiped(Item* itemEquiped)
{
	this->itemEquiped = itemEquiped;
}
