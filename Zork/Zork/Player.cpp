#include "Player.h"



Player::Player()
{
}

Player::Player(Place* actualPlace)
{
	this->actualPlace = actualPlace;
}


Player::~Player()
{
}

Place* Player::getActualPlace()
{
	return actualPlace;
}

void Player::setActualPlace(Place* actualPlace)
{
	this->actualPlace = actualPlace;
}