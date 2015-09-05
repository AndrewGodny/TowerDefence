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

BaseTower::BaseTower(int x, int y)
{
	position.x = x; position.y = y;
	range = 100; radius = 5;
	damage = 0; reload_time = 0;
}

BaseTower::~BaseTower()
{
}

