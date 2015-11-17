#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include <time.h>
#include "Constants.h"

using namespace std;

int main()
{
	Constants constants;

	Place cell("cell", "You're a prisioner of a militia. You wake up in the middle of the night in your cell.");
	Place corridor("corridor", "You're in a corridor with a lot of cells and prisioners sleeping on them. You better escape in silence.");
	Place controlRoom("control room", "Here is the place were the guards control the prisioners and pass their free time.");
	Place armery("armery", "This room is have a lot of guns but unfortunetly you can't find any munition on them.");
	Place corridorUp("corridor", ".");
	Place exit("outside", "Congratulations, you scaped the prision! A woman is waiting you with a car, enjoy your life.");


	cell.setDirection("north", "a door", &corridor, true, "");
	corridor.setDirection("south", "a door", &cell, true, "");
	
	corridor.setDirection("north", "a door", &controlRoom, true, "");
	controlRoom.setDirection("south", "a door", &corridor, true, "");

	controlRoom.setDirection("up", "stairs", &corridorUp, true, "");
	corridorUp.setDirection("down", "stairs", &controlRoom, true, "");

	controlRoom.setDirection("west", "a door", &armery, true, "");
	armery.setDirection("east", "a door", &controlRoom, true, "");

	corridorUp.setDirection("up", "stairs", &exit, true, "");
	vector<Item*> vectorOfItems(0);

	Item note("note", "I opened your cell, run, get out of here before they discover our plan!", true);
	Item paper("paper", "The exit is upstairs but there is an armed guy there. You better go to your west before and arme yourself better. Take care, there's a soldier to but he only have a knife.", true);
	Item knife("knife", "Be fast or die. You can throw me to an enemy but you can miss the hit.", true);
	Item gun("gun", "Be fast or die.", true);
	Item vault("vault", "Put your code (XX-XX-XX) to open the vault. Clue: 01-01-02-03-05-08-...", false, true, &paper, true, "13-21-34");
	Item vault2("vault", "Put your code (XXXX) to open the vault. Clue: 3.1415...", false, true, &gun, true, "9265");

	Item knifeEnemy("knife", "Be fast or die. You can throw me to an enemy but you can miss the hit.", true);
	Item gunEnemy("gun", "Be fast or die.", true);

	vectorOfItems.push_back(&note);
	vectorOfItems.push_back(&paper);
	vectorOfItems.push_back(&knife);
	vectorOfItems.push_back(&knifeEnemy);
	vectorOfItems.push_back(&gunEnemy);
	vectorOfItems.push_back(&gun);
	vectorOfItems.push_back(&vault);
	vectorOfItems.push_back(&vault2);

	cell.addItem(&note);
	controlRoom.addItem(&knife);
	controlRoom.addItem(&vault);
	armery.addItem(&vault2);


	Player player(&cell);
	Enemy enemy1(&knifeEnemy);
	Enemy enemy2(&gunEnemy);

	armery.addEnemy(&enemy1);
	corridorUp.addEnemy(&enemy2);
	player.getActualPlace()->readPlace();

	Place* aux;

	clock_t timeWhenYouEnter = 0;
	bool enemyPresentInTheRoom = false;

	string input;

	while (1) {
		cin >> input;
		switch (constants.selectEnum(input))
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
					cout << itemYouWantToOpen->getMessage() << endl;
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
				if (constants.playerWinsOrLoses("attack", player.getItemEquiped(), player.getActualPlace()->getEnemy()->getItemEquiped(), clock() - timeWhenYouEnter)) {
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
				if (constants.playerWinsOrLoses("throw", player.getItemEquiped(), player.getActualPlace()->getEnemy()->getItemEquiped(), clock() - timeWhenYouEnter)) {
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