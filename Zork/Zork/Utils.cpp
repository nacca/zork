#include "Utils.h"

Utils::Utils()
{

}

Utils::~Utils()
{

}

bool Utils::playerWinsOrLoses(string action, Item* playerItem, Item* enemyItem, clock_t timeSinceEnterRoom) const
{
	if (timeSinceEnterRoom >= 10000)
	{
		if (enemyItem->getName() == "gun")
			cout << "<-- Oh! You have been to slow, the enemy shooted you." << endl;
		else
			cout << "<-- Oh! You have been to slow, the enemy throwed a knife to you." << endl;
		return false;
	}

	else if (playerItem == NULL)
	{
		cout << "<-- You really think that you can kill an armed enemy with your bare hands?" << endl;
		if (enemyItem->getName() == "gun")
			cout << "<-- Of course you can't, the enemy shooted you." << endl;
		else
			cout << "<-- Of course you can't, the enemy doesn't have a gun, but have a knife. He stab you 3 times." << endl;
		return false;
	}

	else if (playerItem->getName() == "knife")
	{
		if (action == "throw")
		{
			cout << "<-- You throw the knife to the soldier and..." << endl;
			srand(time(NULL));
			if ((rand() % 10 + 1) <= 5)
			{
				cout << "<-- PERFECT. You hit the soldier in the heart." << endl;
				return true;
			}
			else
			{
				cout << "<-- BAD. You miss the hit, now the soldier is going to kill you with his weapon." << endl;
				return false;
			}
		}
		else
		{
			if (enemyItem->getName() == "gun")
			{
				cout << "<-- You try to stab the enemy but he has a gun and shoot you in the head while you run to him." << endl;
				return false;
			}
			else
			{
				cout << "<-- You run to the soldier and stab the knife in his chest" << endl;
				return true;
			}
		}
	}
	else
	{
		if (action == "throw")
		{
			cout << "<-- Why on earth you throw a gun to a enemy instead of shooting him?" << endl;
			if (enemyItem->getName() == "gun")
				cout << "<-- The enemy shoot you in the head." << endl;
			else
				cout << "<-- The enemy run to you and stab his knife in your chest" << endl;
			return false;
		}
		else
		{
			cout << "<-- You shoot first and you hit the enemy in the head." << endl;
			return true;
		}
	}
}

InputOrder Utils::selectEnum(string s) const
{
	if (s == "go")
		return InputOrder::GO;

	else if (s == "take")
		return InputOrder::TAKE;

	else if (s == "drop")
		return InputOrder::DROP;

	else if (s == "inventory")
		return InputOrder::INVENTORY;

	else if (s == "exit")
		return InputOrder::EXIT;

	else if (s == "watch")
		return InputOrder::WATCH;

	else if (s == "read" || s == "examine")
		return InputOrder::READ;

	else if (s == "open")
		return InputOrder::OPEN;

	else if (s == "close")
		return InputOrder::CLOSE;

	else if (s == "equip")
		return InputOrder::EQUIP;

	else if (s == "unequip")
		return InputOrder::UNEQUIP;

	else if (s == "attack")
		return InputOrder::ATTACK;

	else if (s == "throw")
		return InputOrder::THROW;

	else if (s == "leave")
		return InputOrder::LEAVE;

	else
		return InputOrder::UNKNOWN;
}
