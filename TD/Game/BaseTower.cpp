#include "BaseTower.h"
#include "SimpleTower.h"

std::shared_ptr<BaseTower> BaseTower::generaeteTower(TowerTypes type, int x, int y)
{
	switch (type)
	{
	case BaseTower::Simple:
		return std::shared_ptr<SimpleTower>(new SimpleTower(x, y));
	default:
		throw std::exception("Undefined tower type");
	}	
}

Point BaseTower::getPosition()
{
	return position;
}

int BaseTower::getRange()
{
	return range;
}

int BaseTower::getRadius()
{
	return radius;
}

int BaseTower::getCost()
{
	return cost;
}

void BaseTower::giveBastard(std::shared_ptr<BaseMonster> m)
{
	bastard = m;
}

BaseTower::BaseTower(int x, int y)
{
	position.x = x; position.y = y;
	range = 100; radius = 5;
	damage = 0; cost = 0;
}

BaseTower::~BaseTower()
{
}

