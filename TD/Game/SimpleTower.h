#pragma once
#include "BaseTower.h"

class SimpleTower :
	public BaseTower
{
	friend BaseTower;

public:
	~SimpleTower();
	TowerTypes getType();

protected:
	SimpleTower(int x, int y);

public:
	void update();
	void draw();
};

