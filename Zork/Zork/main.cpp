#include <iostream>
#include <vector>
#include <string>
#include "Player.h"

using namespace std;

int main()
{
	Place bedroom("Bedroom", "You're in a small bedroom with a bed and a small vault");
	Place corridor("Corridor", "At your right you can see a big glass. If you look through the glass you can see a lot of stars and planets, you're in the space");
	
	//void Place::setDirection(string direction, string definition, Place* nextRoom, bool opened, string itemToOpen)

	bedroom.setDirection("north", "a door", &corridor, true, "");
	corridor.setDirection("south", "a door", &bedroom, true, "");

	vector<Item*> vectorOfItems(0);

	Item keyPaper("paper", "At the first page of the book you can see a 3 set of numbers: \n 01-02-03 \n 05-08-13 \n 21-34-55", true);
	Item key("key", "Nothing to show", true);
	Item vault("vault", "Put your code to open the vault", false, true, &key, false, true, "05-08-13");

	vectorOfItems.push_back(&keyPaper);
	vectorOfItems.push_back(&key);
	vectorOfItems.push_back(&vault);

	bedroom.addItem(&keyPaper);
	bedroom.addItem(&vault);

	Player player(&bedroom);

	player.getActualPlace()->readPlace();

	string input;
	while (1) {
		cin >> input;
		if (input == "exit")
			return 0;
		else if (input == "go") 
		{
			cin >> input;
			Place* aux = player.getActualPlace()->goTo(input);
			if (aux != NULL)
			{
				player.setActualPlace(aux);
				player.getActualPlace()->readPlace();
			}
			else {
				cout << "<-- You can't go in that direction." << endl;
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
		}
		else if (input == "inventory")
		{
			player.readInventory();
		}
		else if (input == "watch")
		{
			player.getActualPlace()->readPlace();
		}
		else if (input == "examine" || input == "read")
		{
			cin >> input;
			player.readItem(input);
		}
		else if (input == "open")
		{
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
					cout << "<-- Error openeing the " << input << "." << endl;
			}
			else
				cout << "<-- You can't open an item that isn't in this place." << endl;			
		}
		else
		{
			cout << "<-- can't recognize the action" << endl;
		}
		cout << endl;
	}
}
