#pragma once

#include <memory>

#include "../defines.h"
#include "BaseMonster.h"

class BaseTower
{
public:
	enum TowerTypes { WideRange, Simple, Spok, Halk };
	static std::shared_ptr<BaseTower> generaeteTower(TowerTypes type, int x, int y);

	virtual ~BaseTower();

	virtual void update();
	virtual void draw() = 0;
	virtual TowerTypes getType() = 0;

	Point getPosition();
	int getRange();
	int getRadius();
	int getCost();
	void giveBastard(std::shared_ptr<BaseMonster> m);

protected:
	BaseTower(int x, int y);	

protected:
	Point position;
	int range, radius;
	int damage;
	int cost;
	std::shared_ptr<BaseMonster> bastard;
};

