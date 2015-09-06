#pragma once
#include "BaseTower.h"

class SimpleTower :
	public BaseTower
{
	friend BaseTower;

public:
	~SimpleTower();
	TowerTypes getType();

	void draw();

protected:
	SimpleTower(int x, int y);

};

