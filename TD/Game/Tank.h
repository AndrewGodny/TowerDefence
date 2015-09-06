#pragma once
#include "BaseMonster.h"
class TankMonster :
	public BaseMonster
{
	friend BaseMonster;
protected:
	TankMonster(int x, int y);

public:
	~TankMonster();

	void draw();
	MonsterTypes getType();
};

