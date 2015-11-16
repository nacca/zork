#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Item* itemEquiped)
{
	this->itemEquiped = itemEquiped;
}

Enemy::~Enemy()
{
}

Item* Enemy::getItemEquiped()
{
	return itemEquiped;
}

void Enemy::setItemEquiped(Item* itemEquiped)
{
	this->itemEquiped = itemEquiped;
}

Item* Enemy::Die()
{
	return itemEquiped;
}