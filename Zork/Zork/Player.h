#include "Place.h"

class Player
{
private:
	Place* actualPlace;

public:
	Player();
	Player(Place* actualPlace);
	~Player();

	Place* getActualPlace();
	void setActualPlace(Place* actualPlace);

};

