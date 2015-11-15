#include "Place.h"

class Entity
{
protected:
	Place* actualPlace;

public:
	Entity();
	Entity(Place* actualPlace);
	virtual ~Entity();

};

