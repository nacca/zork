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

	void setCanTakeIt(bool canTakeIt);
	bool youCanTakeIt();
	bool youCanOpenIt();
	bool needCodeToOpen();
	
	Item* getItemInside();
	string readIt();
	string getMessage(); 
	
	bool checkCode(string code);
	

};

