#include <iostream>
#include "Player.h"

using namespace std;

int main()
{
	Place roomCentral("Habitacio central");
	Place roomNorth("Habitacio north");
	Place roomWest("Habitacio west");
	Place roomNorthUp("Habitacio north-up");
	Place roomWestDown("Habitacio west-down");

	roomCentral.setNorthPlace(&roomNorth);
	roomCentral.setWestPlace(&roomWest);

	roomNorth.setSouthPlace(&roomCentral);
	roomNorth.setUpPlace(&roomNorthUp);

	roomWest.setEastPlace(&roomCentral);
	roomWest.setDownPlace(&roomWestDown);

	roomNorthUp.setDownPlace(&roomNorth);

	roomWestDown.setUpPlace(&roomWest);

	Player player(&roomCentral);

	string input;
	while (1) {
		player.getActualPlace()->readPlace();
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
					player.setActualPlace(player.getActualPlace()->getNorthPlace());
			}
			else if (input == "south")
			{
				if (player.getActualPlace()->getSouthPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					player.setActualPlace(player.getActualPlace()->getSouthPlace());
			}
			else if (input == "east")
			{
				if (player.getActualPlace()->getEastPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					player.setActualPlace(player.getActualPlace()->getEastPlace());
			}
			else if (input == "west")
			{
				if (player.getActualPlace()->getWestPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					player.setActualPlace(player.getActualPlace()->getWestPlace());
			}
			else if (input == "up")
			{
				if (player.getActualPlace()->getUpPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					player.setActualPlace(player.getActualPlace()->getUpPlace());
			}
			else if (input == "down")
			{
				if (player.getActualPlace()->getDownPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					player.setActualPlace(player.getActualPlace()->getDownPlace());
			}
			else
			{
				cout << "no t'entenc" << endl;
			}
		}
		else {
			cout << "no t'entenc" << endl;
		}
		cout << endl;
	}
}
