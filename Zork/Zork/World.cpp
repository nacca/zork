#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::Init()
{
	// Create new player
	player = Player();

	// Create new enemies
	enemy1 = Enemy();
	enemy2 = Enemy();

	// Create rooms
	cell = Place("cell", "You're a prisoner of the militia and you wake up in the middle of the night in your cell.");
	corridor = Place("corridor", "You're in a corridor with a lot of cells and prisoners sleeping on them. You better escape in silence.");
	controlRoom = Place("control room", "You're in the control room, this is the place where the guards control the prisoners and pass their free time.");
	armory = Place("armory", "You're in the armory, this room is have a lot of guns but unfortunately you can't find any munition on them.");
	corridorUp = Place("corridor", "You're in the last corridor of the prison, you have the escape in front of you.");
	exit = Place("outside", "Congratulations, you escaped the prison! A woman is waiting you with a car, enjoy your life.");

	// Create items
	note = Item("note", "I opened your cell, run, get out of here before they discover our plan!", true);
	paper = Item("paper", "The exit is upstairs but there is an armed guy there. You better go to your west before and arm yourself better. Take care, there's a soldier too but he only has a knife.", true);
	knife = Item("knife", "Be fast or die. You can throw me to an enemy but you can miss the hit.", true);
	gun = Item("gun", "Be fast or die.", true);
	vault = Item("vault", "Put your code (XX-XX-XX) to open the vault. Clue: 01-01-02-03-05-08-...", false, true, false, true, &paper, true, "13-21-34");
	vault2 = Item("vault", "Put your code (XXXX) to open the vault. Clue: 3.1415...", false, true, false, true, &gun, true, "9265");
	knifeEnemy = Item("knife", "Be fast or die. You can throw me to an enemy but you can miss the hit.", true);
	gunEnemy = Item("gun", "Be fast or die.", true);

	gun.putInsideOfAnItem(&vault2);
	paper.putInsideOfAnItem(&vault);

	// Filling rooms

	cell.setDirection("north", "a door", &corridor, true, "");
	corridor.setDirection("south", "a door", &cell, true, "");

	corridor.setDirection("north", "a door", &controlRoom, true, "");
	controlRoom.setDirection("south", "a door", &corridor, true, "");

	controlRoom.setDirection("up", "stairs", &corridorUp, true, "");
	corridorUp.setDirection("down", "stairs", &controlRoom, true, "");

	controlRoom.setDirection("west", "a door", &armory, true, "");
	armory.setDirection("east", "a door", &controlRoom, true, "");

	corridorUp.setDirection("up", "stairs", &exit, true, "");

	enemy1.setItemEquiped(&knifeEnemy);
	enemy2.setItemEquiped(&gunEnemy);

	cell.addItem(&note);
	controlRoom.addItem(&knife);
	controlRoom.addItem(&vault);
	armory.addItem(&vault2);

	armory.addEnemy(&enemy1);
	corridorUp.addEnemy(&enemy2);

	//

	player.setActualPlace(&cell);

	timeWhenYouEnter = 0;
	enemyPresentInTheRoom = false;

	player.getActualPlace()->readPlace();
}

int World::Iteration(InputOrder io)
{
	string input;

	switch (io)
	{
	case InputOrder::EXIT:
		return 2;
		break;

	case InputOrder::GO:

		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << "<-- You can't do that, you have an enemy in the room!" << endl;
		}
		else if (player.getActualPlace()->goTo(input) != NULL)
		{
			player.setActualPlace(player.getActualPlace()->goTo(input));
			player.getActualPlace()->readPlace();
			
			if (player.getActualPlace()->getName() == "outside")
			{
				cout << "<-- What you wanna do now? Write 'restart' to play again or 'end' to close de game" << endl;
				while (1)
				{
					cin >> input;
					if (input == "restart")
						return 1;
					else if (input == "end")
						return 2;
				}
			}
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
		if (enemyPresentInTheRoom)
		{
			cout << "<-- You can't do that, you have an enemy in the room!" << endl;
		}
		else if (player.getActualPlace()->isItemPresent(input))
		{
			Item* itemYouWantToTake = player.getActualPlace()->getItemByName(input);

			if (itemYouWantToTake->youCanTakeIt())
			{
				if (player.isItemInTheInventory(itemYouWantToTake->getName()))
					cout << "<-- You already have the same item in the inventory." << endl;
				else
				{
					if (itemYouWantToTake->isInsideAnItem()) {
						itemYouWantToTake->getItemOutside()->takeItem();
						itemYouWantToTake->takeOutsideItem();
					}
					player.getActualPlace()->removeItem(itemYouWantToTake);
					player.addItem(itemYouWantToTake);
					cout << "<-- " << input << " taken" << endl;
				}
			}
			else
			{
				cout << "<-- This item can't be removed." << endl;
			}
		}
		else
		{
			cout << "<-- This item can't be founded in this place." << endl;
		}
		cout << endl;
		break;

	case InputOrder::DROP:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << "<-- You can't do that, you have an enemy in the room!" << endl;
		}
		else if ((player.isItemInTheInventory(input) && player.getItemEquiped() == NULL) ||
			(player.isItemInTheInventory(input) && player.getItemEquiped()->getName() != input))
		{
			Item* itemYouWantToTake = player.getItemByName(input);

			player.removeItem(itemYouWantToTake);
			player.getActualPlace()->addItem(itemYouWantToTake);
			cout << "<-- " << input << " droped" << endl;
		}
		else if (player.getItemEquiped() == NULL || player.getItemEquiped()->getName() != input)
			cout << "<-- You don't have this item." << endl;
		else
		{
			cout << "<-- You can't drop an item if you have it equipped." << endl;
		}
		cout << endl;
		break;

	case InputOrder::INVENTORY:
		player.readInventory();
		cout << endl;
		break;

	case InputOrder::WATCH:
		player.getActualPlace()->readPlace();
		break;

	case InputOrder::READ:
		cin >> input;
		player.readItem(input);
		cout << endl;
		break;

	case InputOrder::OPEN:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << "<-- You can't do that, you have an enemy in the room!" << endl;
		}
		else if (player.getActualPlace()->isItemPresent(input))
		{
			Item* itemYouWantToOpen = player.getActualPlace()->getItemByName(input);

			if (itemYouWantToOpen->isOpened())
				cout << "<-- The item is already opened" << endl;
			else
			{
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
					itemYouWantToOpen->open();
					if (itemYouWantToOpen->haveAnItemInside())
					{
						player.getActualPlace()->addItem(itemYouWantToOpen->getItemInside());
						cout << "<-- " << input << " opened. Inside it you can see a " << itemYouWantToOpen->getItemInside()->getName() << "." << endl;
					}
					else
					{
						cout << "<-- " << input << " opened. There's nothing inside." << endl;
					}
				}
				else
					cout << "<-- Wrong code." << endl;
			}
		}
		else
			cout << "<-- You can't open an item that isn't in this place." << endl;
		cout << endl;
		break;

	case InputOrder::CLOSE:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cout << "<-- You can't do that, you have an enemy in the room!" << endl;
		}
		else if (player.getActualPlace()->isItemPresent(input))
		{
			Item* itemYouWantToClose = player.getActualPlace()->getItemByName(input);

			if (!itemYouWantToClose->youCanOpenIt())
				cout << "<-- You can't open/close that item" << endl;
			else if (!itemYouWantToClose->isOpened())
				cout << "<-- The item is already closed" << endl;
			else
			{
				if (itemYouWantToClose->haveAnItemInside())
				{
					player.getActualPlace()->removeItem(itemYouWantToClose->getItemInside());
				}
				itemYouWantToClose->close();
				cout << "<-- " << itemYouWantToClose->getName() << " closed." << endl;
			}
		}
		else
			cout << "<-- You can't close an item that isn't in this place." << endl;
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
			if (utils.playerWinsOrLoses("attack", player.getItemEquiped(), player.getActualPlace()->getEnemy()->getItemEquiped(), clock() - timeWhenYouEnter)) {
				Item* dropItem = player.getActualPlace()->getEnemy()->getItemEquiped();
				enemyPresentInTheRoom = false;
				player.getActualPlace()->enemyDies();
				cout << "<-- Congratulations, you killed the enemy!" << endl;
				cout << "<-- Enemy dead, he droped a " << dropItem->getName() << "." << endl;
			}
			else
			{
				cout << "<-- You are dead, write 'restart' if you wanna play again or 'end' if you wanna close the game." << endl;
				while (1)
				{
					cin >> input;
					if (input == "restart")
						return 1;
					else if (input == "end")
						return 2;
				}
			}
		}
		else
		{
			cout << "<-- You can't attack someone who isn't in the room" << endl;
		}
		cout << endl;
		break;

	case InputOrder::THROW:
		if (enemyPresentInTheRoom)
		{
			if (utils.playerWinsOrLoses("throw", player.getItemEquiped(), player.getActualPlace()->getEnemy()->getItemEquiped(), clock() - timeWhenYouEnter)) {
				Item* dropItem = player.getActualPlace()->getEnemy()->getItemEquiped();
				enemyPresentInTheRoom = false;
				player.getActualPlace()->enemyDies();
				cout << "<-- Congratulations, you killed the enemy!" << endl;
				cout << "<-- Enemy dead, he droped a " << dropItem->getName() << "." << endl;
			}
			else
			{
				cout << "<-- You are dead, write 'restart' if you wanna play again or 'end' if you wanna close the game." << endl;
				while (1)
				{
					cin >> input;
					if (input == "restart")
						return 1;
					else if (input == "end")
						return 2;
				}
			}
		}
		else
		{
			cout << "<-- You can't attack someone who isn't in the room." << endl;
		}
		cout << endl;
		break;

	case InputOrder::LEAVE:
		cin >> input;
		if (enemyPresentInTheRoom)
		{
			cin >> input; cin >> input;
			cout << "<-- You can't do that, you have an enemy in the room!" << endl;
		}
		else if ((player.isItemInTheInventory(input) && player.getItemEquiped() == NULL) ||
			(player.isItemInTheInventory(input) && player.getItemEquiped()->getName() != input))
		{
			Item* itemToLeave = player.getItemByName(input);
			cin >> input;
			if (input == "inside")
			{
				cin >> input;
				Item* itemWhereLeave = player.getActualPlace()->getItemByName(input);

				if (!itemWhereLeave->youCanOpenIt())
					cout << "<-- You can't leave an item inside the " << itemWhereLeave->getName() << endl;
				else if (!itemWhereLeave->isOpened())
					cout << "<-- The " << itemWhereLeave->getName() << " is closed." << endl;
				else if (itemWhereLeave->haveAnItemInside())
					cout << "<-- The " << itemWhereLeave->getName() << " already have an item inside" << endl;
				else
				{
					itemToLeave->putInsideOfAnItem(itemWhereLeave);
					itemWhereLeave->putItem(itemToLeave);
					player.getActualPlace()->addItem(itemToLeave);
					player.removeItem(itemToLeave);
					cout << "<-- You have left the " << itemToLeave->getName() << " inside the " << itemWhereLeave->getName() << endl;
				}
			}
		}
		else if (player.getItemEquiped() == NULL || player.getItemEquiped()->getName() != input)
		{
			cin >> input; cin >> input;
			cout << "<-- You don't have this item." << endl;
		}
		else
		{
			cin >> input; cin >> input;
			cout << "<-- You can't drop an item if you have it equiped." << endl;
		}
		cout << endl;
		break;

	default:
		cin >> input;
		cout << "<-- I can't recognize the action." << endl;
		cout << endl;
		break;

	}

	return 0;
}