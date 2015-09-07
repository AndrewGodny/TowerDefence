#include "BaseTower.h"
#include "SimpleTower.h"
#include "WideRangeTower.h"
#include "Halk.h"
#include "SpokTower.h"

std::shared_ptr<BaseTower> BaseTower::generaeteTower(TowerTypes type, int x, int y)
{
	switch (type)
	{
	case BaseTower::Simple:
		return std::shared_ptr<SimpleTower>(new SimpleTower(x, y));
	case BaseTower::WideRange:
		return std::shared_ptr<WideRangeTower>(new WideRangeTower(x, y));
	case BaseTower::Halk:
		return std::shared_ptr<HalkTower>(new HalkTower(x, y));
	case BaseTower::Spok:
		return std::shared_ptr<SpokTower>(new SpokTower(x, y));
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
	damage = 0; cost = 100;
}

BaseTower::~BaseTower()
{
}

void BaseTower::update()
{
	if (bastard != nullptr) {		
		if (bastard->isAlive()) bastard->hit(damage);
		if (!bastard->isAlive()) bastard = nullptr;
		else
			if (Point::distance(position, bastard->getPosition()) > range) bastard = nullptr;
	}
}

