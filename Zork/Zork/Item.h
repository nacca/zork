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
	bool needKey;
	string code;
	Item* itemInside;

public:
	Item();
	Item(string name, string message, bool canTakeIt);
	Item(string name, string message, bool canTakeIt, bool canBeOpened, Item* itemInside);
	Item(string name, string message, bool canTakeIt, bool canBeOpened, Item* itemInside, bool needKey, bool needCode, string code);
	~Item();

	string getName();
	void setName(string name);

	bool youCanTakeIt();
	bool youCanOpenIt();
	bool needKeyToOpen();
	bool needCodeToOpen();
	Item* getItemInside();
	string readIt();
	void setCanTakeIt(bool canTakeIt);
	bool checkCode(string code);
};

