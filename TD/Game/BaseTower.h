#pragma once

#include <memory>

#include "../defines.h"

class BaseTower
{
public:
	enum TowerTypes { Simple };
	static std::shared_ptr<BaseTower> generaeteTower(TowerTypes type, int x, int y);

	virtual ~BaseTower();

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual TowerTypes getType() = 0;

	Point getPosition();
	int getRange();
	int getRadius();

protected:
	BaseTower(int x, int y);	

protected:
	Point position;
	int range, radius;
	int damage;
	int reload_time;
};

