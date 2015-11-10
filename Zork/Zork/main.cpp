#include <iostream>
#include <string>
#include "Place.h"

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

	Place* actualRoom = &roomCentral;

	string input;
	while (1) {
		actualRoom->readPlace();
		cin >> input;
		if (input == "exit")
			return 0;
		else if (input == "go") 
		{
			cin >> input;
			if (input == "north")
			{
				if (actualRoom->getNorthPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					actualRoom = actualRoom->getNorthPlace();
			}
			else if (input == "south")
			{
				if (actualRoom->getSouthPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					actualRoom = actualRoom->getSouthPlace();
			}
			else if (input == "east")
			{
				if (actualRoom->getEastPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					actualRoom = actualRoom->getEastPlace();
			}
			else if (input == "west")
			{
				if (actualRoom->getWestPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					actualRoom = actualRoom->getWestPlace();
			}
			else if (input == "up")
			{
				if (actualRoom->getUpPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					actualRoom = actualRoom->getUpPlace();
			}
			else if (input == "down")
			{
				if (actualRoom->getDownPlace() == NULL)
					cout << "No hi ha habitacio cap on vols anar" << endl;
				else
					actualRoom = actualRoom->getDownPlace();
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
