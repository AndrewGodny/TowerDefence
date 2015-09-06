#pragma once
#include "BaseTower.h"
class HalkTower :
	public BaseTower
{
	friend BaseTower;
protected:
	HalkTower(int x, int y);

public:
	~HalkTower();

	TowerTypes getType();

	void draw();
};

