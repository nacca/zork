#include "Entity.h"

class Enemy: public Entity
{
public:
	Enemy();
	Enemy(Place* actualPlace);
	~Enemy();
};

