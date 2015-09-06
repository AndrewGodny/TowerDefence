#pragma once
#include "BaseTower.h"
class SpokTower :
	public BaseTower
{
	friend BaseTower;

protected:
	SpokTower(int x, int y);

public:
	~SpokTower();

	TowerTypes getType();

	void draw();
};

