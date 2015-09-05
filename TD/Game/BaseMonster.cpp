#include "BaseMonster.h"
#include "SimpleMonster.h"


Point BaseMonster::getPosition()
{
	return position;
}

int BaseMonster::getHp()
{
	return hp;
}

int BaseMonster::getSpeed()
{
	return speed;
}

BaseMonster::BaseMonster(int x, int y)
{
	position.x = x;
	position.y = y;
	speed = 0; hp = 100;
	size = 5;
}


std::shared_ptr<BaseMonster> BaseMonster::generateMonster(MonsterTypes type, int x, int y)
{
	switch (type)
	{
	case BaseMonster::Simple:
		return std::shared_ptr<SimpleMonster>(new SimpleMonster(x, y));
	default:
		throw std::exception("Undefined tower type");
	}
}

BaseMonster::~BaseMonster()
{
}
