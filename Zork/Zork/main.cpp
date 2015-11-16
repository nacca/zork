#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include <time.h>
#include "Constants.h"

using namespace std;

enum class InputOrder { GO, TAKE, DROP, INVENTORY, EXIT, WATCH, READ, OPEN, EQUIP, UNEQUIP, ATTACK, THROW, UNKNOWN };

InputOrder selectEnum(string s)
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

	else if (s == "equip")
		return InputOrder::EQUIP;

	else if (s == "unequip")
		return InputOrder::UNEQUIP;

	else if (s == "attack")
		return InputOrder::ATTACK;

	else if (s == "throw")
		return InputOrder::THROW;
	
	else
		return InputOrder::UNKNOWN;
}

const bool playerWinsOrLoses(string action, Item* playerItem, Item* enemyItem, clock_t timeSinceEnterRoom)
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

int main()
{
	Constants constants();

	Place bedroom("Bedroom", "You're in a small bedroom with a bed and a small vault");
	Place corridor("Corridor", "At your right you can see a big glass. If you look through the glass you can see a lot of stars and planets, you're in the space");
	
	//void Place::setDirection(string direction, string definition, Place* nextRoom, bool opened, string itemToOpen)

	bedroom.setDirection("north", "a door", &corridor, true, "");
	corridor.setDirection("south", "a door", &bedroom, true, "");

	vector<Item*> vectorOfItems(0);

	Item keyPaper("paper", "You can see 3 set of numbers: \n 01-02-03 \n 05-08-13 \n 21-34-55", true);
	Item knife("knife", "Be fast or die. You can throw me to an enemy.", true);
	Item gun("gun", "Be fast or die.", true);
	Item vault("vault", "Put your code to open the vault", false, true, &knife, true, "05-08-13");

	vectorOfItems.push_back(&keyPaper);
	vectorOfItems.push_back(&knife);
	vectorOfItems.push_back(&vault);

	bedroom.addItem(&keyPaper);
	bedroom.addItem(&vault);

	Player player(&bedroom);
	Enemy enemy1(&gun);

	corridor.addEnemy(&enemy1);
	player.getActualPlace()->readPlace();

	Place* aux;

	clock_t timeWhenYouEnter = 0;
	bool enemyPresentInTheRoom = false;

	string input;

	while (1) {
		cin >> input;
		switch (selectEnum(input))
		{
		case InputOrder::EXIT:
			return 0;
			break;

		case InputOrder::GO:
			cin >> input;
			aux = player.getActualPlace()->goTo(input);
			if (aux != NULL)
			{
				player.setActualPlace(aux);
				player.getActualPlace()->readPlace();
				if (player.getActualPlace()->isEnemyPresent())
				{
					enemyPresentInTheRoom = true;
					timeWhenYouEnter = clock();
				}
				else
				{
					enemyPresentInTheRoom = false;
				}
			}
			else {
				cout << "<-- You can't go in that direction." << endl;
			}
			cout << endl;
			break;

		case InputOrder::TAKE:
			cin >> input;
			if (player.getActualPlace()->isItemPresent(input))
			{
				bool itemFinded = false;
				Item* itemYouWantToTake = NULL;
				for (int i = 0; i < vectorOfItems.size() && !itemFinded; ++i)
				{
					if (vectorOfItems[i]->getName() == input)
					{
						itemYouWantToTake = vectorOfItems[i];
						itemFinded = true;
					}
				}

				if (itemYouWantToTake->youCanTakeIt())
				{
					player.getActualPlace()->removeItem(itemYouWantToTake);
					player.addItem(itemYouWantToTake);
					cout << "<-- " << input << " taken" << endl;
				}
				else
				{
					cout << "<-- This item can't be removed" << endl;
				}
			}
			else
			{
				cout << "<-- This item can't be founded in this place" << endl;
			}
			cout << endl;
			break;

		case InputOrder::DROP:
			cin >> input;
			if (player.isItemInTheInventory(input))
			{
				bool itemFinded = false;
				Item* itemYouWantToTake = NULL;
				for (int i = 0; i < vectorOfItems.size() && !itemFinded; ++i)
				{
					if (vectorOfItems[i]->getName() == input)
					{
						itemYouWantToTake = vectorOfItems[i];
						itemFinded = true;
					}
				}

				if (itemYouWantToTake->youCanTakeIt())
				{
					player.removeItem(itemYouWantToTake);
					player.getActualPlace()->addItem(itemYouWantToTake);
					cout << "<-- " << input << " droped" << endl;
				}
				else
				{
					cout << "<-- This item can't be removed" << endl;
				}
			}
			else
			{
				cout << "<-- This item can't be founded in this place" << endl;
			}
			cout << endl;
			break;

		case InputOrder::INVENTORY:
			player.readInventory();
			cout << endl;
			break;

		case InputOrder::WATCH:
			player.getActualPlace()->readPlace();
			cout << endl;
			break;

		case InputOrder::READ:
			cin >> input;
			player.readItem(input);
			cout << endl;
			break;

		case InputOrder::OPEN:
			cin >> input;
			if (player.getActualPlace()->isItemPresent(input))
			{
				bool itemFinded = false;
				Item* itemYouWantToOpen = NULL;
				for (int i = 0; i < vectorOfItems.size() && !itemFinded; ++i)
				{
					if (vectorOfItems[i]->getName() == input)
					{
						itemYouWantToOpen = vectorOfItems[i];
						itemFinded = true;
					}
				}
				bool opened = false;
				if (itemYouWantToOpen->needCodeToOpen())
				{
					cout << "<-- Put the code (codes have the format XX-XX-XX):" << endl;
					string codeByUser;
					cin >> codeByUser;
					if (itemYouWantToOpen->checkCode(codeByUser))
						opened = true;
				}
				else
					opened = true;
				if (opened)
				{
					player.getActualPlace()->addItem(itemYouWantToOpen->getItemInside());
					cout << "<-- " << input << " opened. Inside it you can see a " << itemYouWantToOpen->getItemInside()->getName() << "." << endl;
				}
				else
					cout << "<-- Wrong code." << endl;
			}
			else
				cout << "<-- You can't open an item that isn't in this place." << endl;
			cout << endl;
			break;

		case InputOrder::EQUIP:
			cin >> input;
			player.equipItem(input);
			cout << endl;
			break;

		case InputOrder::UNEQUIP:
			player.unequipItem();
			cout << endl;
			break;

		case InputOrder::ATTACK:
			if (enemyPresentInTheRoom)
			{
				if (playerWinsOrLoses("attack", player.getItemEquiped(), player.getActualPlace()->getEnemy()->getItemEquiped(), clock() - timeWhenYouEnter)) {
					Item* dropItem = player.getActualPlace()->getEnemy()->Die();
					enemyPresentInTheRoom = false;
					player.getActualPlace()->enemyDies();
					cout << "<-- Congratulations, you killed the enemy!" << endl;
					cout << "<-- Enemy dead, he droped a " << dropItem->getName() << "." << endl;
				}
				else
					cout << "<-- You die, need to restart the game." << endl;
			}
			else
			{
				cout << "<-- You can't attack someone who isn't in the room" << endl;
			}
			break;

		case InputOrder::THROW:
			if (enemyPresentInTheRoom)
			{
				if (playerWinsOrLoses("throw", player.getItemEquiped(), player.getActualPlace()->getEnemy()->getItemEquiped(), clock() - timeWhenYouEnter)) {
					Item* dropItem = player.getActualPlace()->getEnemy()->Die();
					enemyPresentInTheRoom = false;
					player.getActualPlace()->enemyDies();
					cout << "<-- Congratulations, you killed the enemy!" << endl;
					cout << "<-- Enemy dead, he droped a " << dropItem->getName() << "." << endl;
				}
				else
					cout << "<-- You die, need to restart the game." << endl;
			}
			else
			{
				cout << "<-- You can't attack someone who isn't in the room" << endl;
			}
			break;

		default:
			cout << "<-- can't recognize the action" << endl;
			cout << endl;
			break;

		}
	}
}