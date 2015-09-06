#pragma once
#include "BaseMonster.h"
class QuickMonster :
	public BaseMonster
{
	friend BaseMonster;
protected:
	QuickMonster(int x, int y);

public:
	~QuickMonster();

	void draw();
	MonsterTypes getType();
};

