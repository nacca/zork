#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

int main()
{
	Place roomCentral("Habitacio central");
	Place roomNorth("Habitacio north");
	Place roomWest("Habitacio west");
	Place roomNorthUp("Habitacio north-up");
	Place roomWestDown("Habitacio west-down");

	vector<Item*> vectorOfItems(0);

	Item knife("knife", true);
	Item gun("gun", true);
	Item painting("painting", false);
	Item trophie("trophie", false);
	Item rope("rope", true);

	vectorOfItems.push_back(&knife);
	vectorOfItems.push_back(&gun);
	vectorOfItems.push_back(&painting);
	vectorOfItems.push_back(&trophie);
	vectorOfItems.push_back(&rope);

	roomCentral.setNorthPlace(&roomNorth);
	roomCentral.setWestPlace(&roomWest);
	roomCentral.addItem(&knife);

	roomNorth.setSouthPlace(&roomCentral);
	roomNorth.setUpPlace(&roomNorthUp);
	roomNorth.addItem(&gun);

	roomWest.setEastPlace(&roomCentral);
	roomWest.setDownPlace(&roomWestDown);
	roomWest.addItem(&painting);

	roomNorthUp.setDownPlace(&roomNorth);
	roomNorthUp.addItem(&trophie);

	roomWestDown.setUpPlace(&roomWest);
	roomWestDown.addItem(&rope);

	Player player(&roomCentral);

	player.getActualPlace()->readPlace();

	string input;
	while (1) {
		cin >> input;
		if (input == "exit")
			return 0;
		else if (input == "go") 
		{
			cin >> input;
			if (input == "north")
			{
				if (player.getActualPlace()->getNorthPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
				{
					player.setActualPlace(player.getActualPlace()->getNorthPlace());
					player.getActualPlace()->readPlace();
				}

			}
			else if (input == "south")
			{
				if (player.getActualPlace()->getSouthPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
				{
					player.setActualPlace(player.getActualPlace()->getSouthPlace());
					player.getActualPlace()->readPlace();
				}
			}
			else if (input == "east")
			{
				if (player.getActualPlace()->getEastPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
				{
					player.setActualPlace(player.getActualPlace()->getEastPlace());
					player.getActualPlace()->readPlace();
				}
			}
			else if (input == "west")
			{
				if (player.getActualPlace()->getWestPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
				{
					player.setActualPlace(player.getActualPlace()->getWestPlace());
					player.getActualPlace()->readPlace();
				}
			}
			else if (input == "up")
			{
				if (player.getActualPlace()->getUpPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
				{
					player.setActualPlace(player.getActualPlace()->getUpPlace());
					player.getActualPlace()->readPlace();
				}
			}
			else if (input == "down")
			{
				if (player.getActualPlace()->getDownPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
				{
					player.setActualPlace(player.getActualPlace()->getDownPlace());
					player.getActualPlace()->readPlace();
				}
			}
			else
			{
				cout << "no t'entenc" << endl;
			}
		}
		else if (input == "take")
		{
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
					cout << input << " taken" << endl;
				}
				else
				{
					cout << "This item can't be removed" << endl;
				}
			}
			else
			{
				cout << "This item can't be founded in this place" << endl;
			}
		}
		else if (input == "drop")
		{
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
					cout << input << " droped" << endl;
				}
				else
				{
					cout << "This item can't be removed" << endl;
				}
			}
			else
			{
				cout << "This item can't be founded in this place" << endl;
			}
		}
		else if (input == "inventory")
		{
			player.readInventory();
		}
		else if (input == "watch")
		{
			player.getActualPlace()->readPlace();
		}
		else
		{
			cout << "no t'entenc" << endl;
		}
		cout << endl;
	}
}
