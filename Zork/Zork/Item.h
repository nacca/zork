#include <string>

using namespace std;

class Item
{
private:
	string name;
	bool canTakeIt;

public:
	Item();
	Item(string name, bool canTakeIt);
	~Item();

	string getName();
	void setName(string name);

	bool youCanTakeIt();
	void setCanTakeIt(bool canTakeIt);

};

