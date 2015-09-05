#pragma once
#include "BaseMonster.h"

class SimpleMonster :
	public BaseMonster
{
	friend BaseMonster;
public:	
	~SimpleMonster();

	void update();
	void draw();
	MonsterTypes getType();

protected:
	SimpleMonster(int x, int y);
};

