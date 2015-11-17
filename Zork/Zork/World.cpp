#include "World.h"



World::World()
{
}


World::~World()
{
}

void World::Init()
{
	player = Player();

	enemy1 = Enemy();
	enemy2 = Enemy();

	cell = Place ("cell", "You're a prisioner of a militia. You wake up in the middle of the night in your cell.");
	corridor = Place ("corridor", "You're in a corridor with a lot of cells and prisioners sleeping on them. You better escape in silence.");
	controlRoom = Place ("control room", "Here is the place were the guards control the prisioners and pass their free time.");
	armery = Place ("armery", "This room is have a lot of guns but unfortunetly you can't find any munition on them.");
	corridorUp = Place ("corridor", ".");
	exit = Place ("outside", "Congratulations, you scaped the prision! A woman is waiting you with a car, enjoy your life.");

	note = Item ("note", "I opened your cell, run, get out of here before they discover our plan!", true);
	paper = Item ("paper", "The exit is upstairs but there is an armed guy there. You better go to your west before and arme yourself better. Take care, there's a soldier to but he only have a knife.", true);
	knife = Item ("knife", "Be fast or die. You can throw me to an enemy but you can miss the hit.", true);
	gun = Item ("gun", "Be fast or die.", true);
	vault = Item ("vault", "Put your code (XX-XX-XX) to open the vault. Clue: 01-01-02-03-05-08-...", false, true, &paper, true, "13-21-34");
	vault2 = Item ("vault", "Put your code (XXXX) to open the vault. Clue: 3.1415...", false, true, &gun, true, "9265");
	knifeEnemy = Item ("knife", "Be fast or die. You can throw me to an enemy but you can miss the hit.", true);
	gunEnemy = Item ("gun", "Be fast or die.", true);

	//

	cell.setDirection("north", "a door", &corridor, true, "");
	corridor.setDirection("south", "a door", &cell, true, "");

	corridor.setDirection("north", "a door", &controlRoom, true, "");
	controlRoom.setDirection("south", "a door", &corridor, true, "");

	controlRoom.setDirection("up", "stairs", &corridorUp, true, "");
	corridorUp.setDirection("down", "stairs", &controlRoom, true, "");

	controlRoom.setDirection("west", "a door", &armery, true, "");
	armery.setDirection("east", "a door", &controlRoom, true, "");

	corridorUp.setDirection("up", "stairs", &exit, true, "");

	player.setActualPlace(&cell);

	enemy1.setItemEquiped(&knifeEnemy);
	enemy2.setItemEquiped(&gunEnemy);

	cell.addItem(&note);
	controlRoom.addItem(&knife);
	controlRoom.addItem(&vault);
	armery.addItem(&vault2);

	armery.addEnemy(&enemy1);
	corridorUp.addEnemy(&enemy2);

	//

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
			Item* itemYouWantToTake = player.getActualPlace()->getItemByName(input);

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
			Item* itemYouWantToTake = player.getItemByName(input);

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
			Item* itemYouWantToOpen = player.getActualPlace()->getItemByName(input);

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
			{
				cout << "<-- You die, write 'restart' if you wanna play again or 'end' if you wanna close the game." << endl;
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
			{
				cout << "<-- You die, write 'restart' if you wanna play again or 'end' if you wanna close the game." << endl;
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
		break;

	default:
		cout << "<-- can't recognize the action" << endl;
		cout << endl;
		break;

	}
	return 0;
}