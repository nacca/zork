#include <iostream>
#include <vector>
#include <string>
#include "Constants.h"
#include "World.h"

using namespace std;

int main()
{
	cout << "Welcome to my Zork! By Oriol Romero." << endl;
	cout << "________________________________________" << endl;
	cout << endl;

	Constants constants;
	World world;
	world.Init();

	string input;

	while (1) {
		cin >> input;
		int instruction = world.Iteration(constants.selectEnum(input));
		if (instruction == 2)
			return 0;
		else if (instruction == 1)
		{
			cout << endl;
			cout << endl;
			cout << endl;
			world.Init();
		}
	}
}