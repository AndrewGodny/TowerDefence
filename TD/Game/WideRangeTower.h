#pragma once
#include "BaseTower.h"
class WideRangeTower :
	public BaseTower
{
	friend BaseTower;
protected:
	WideRangeTower(int x, int y);

public:
	~WideRangeTower();

	TowerTypes getType();

	void draw();
};

