#pragma once
#include <memory>
#include "../defines.h"

class BaseMonster
{
public:	
	enum MonsterTypes { Simple };
	static std::shared_ptr<BaseMonster> generateMonster(MonsterTypes type, int x, int y);
	
	virtual ~BaseMonster();

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual MonsterTypes getType() = 0;

	Point getPosition();
	int getHp();
	int getSpeed();

protected:
	BaseMonster(int x, int y);

protected:
	Point position;
	int hp;
	int speed;
	int size;
};

