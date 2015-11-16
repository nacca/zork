#include "Constants.h"

Constants::Constants()
{

}

Constants::~Constants()
{

}


const bool Constants::playerWinsOrLoses(string action, Item* playerItem, Item* enemyItem, clock_t timeSinceEnterRoom)
{
	if (timeSinceEnterRoom >= 5000)
	{
		if (enemyItem->getName() == "gun")
			cout << "<-- Oh! You have been to slow, the enemy shooted you." << endl;
		else
			cout << "<-- Oh! You have been to slow, the enemy throwed the knife to you." << endl;
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
				cout << "<-- You started a knife battle..." << endl;
				srand(time(NULL));
				if ((rand() % 10 + 1) <= 5)
				{
					cout << "<-- PERFECT. You hit the soldier in the heart." << endl;
					return true;
				}
				else
				{
					cout << "<-- BAD. You miss the hit and the soldier stab you in your heart." << endl;
					return false;
				}
			}
		}
	}
	else
	{
		cout << "<-- You shoot first and you hit the enemy in the head." << endl;
		return true;
	}
}