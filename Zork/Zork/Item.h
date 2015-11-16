#pragma once
#include <string>
using namespace std;

class Item
{
private:
	string name;
	string message;
	bool canTakeIt;
	bool canBeOpened;
	bool needCode;
	string code;
	Item* itemInside;

public:
	Item();
	Item(string name, string message, bool canTakeIt);
	Item(string name, string message, bool canTakeIt, bool canBeOpened, Item* itemInside);
	Item(string name, string message, bool canTakeIt, bool canBeOpened, Item* itemInside, bool needCode, string code);
	~Item();

	string getName();
	void setName(string name);

	bool youCanTakeIt();
	bool youCanOpenIt();
	bool needCodeToOpen();
	Item* getItemInside();
	string readIt();
	void setCanTakeIt(bool canTakeIt);
	bool checkCode(string code);
};

