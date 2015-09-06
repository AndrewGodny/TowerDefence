#pragma once
#include <memory>
#include "../defines.h"

class BaseMonster
{
public:	
	enum MonsterTypes { Simple, End } types;
	static std::shared_ptr<BaseMonster> generateMonster(MonsterTypes type, int x, int y);
	
	virtual ~BaseMonster();

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual MonsterTypes getType() = 0;

	Point getPosition();
	int getHp();
	int getSpeed();
	int getCost();

	bool isAlive();
	void setPath(Path p);
	void hit(int damage);

protected:
	BaseMonster(int x, int y);

protected:
	Point position;
	Path path;
	int cost;
	int hp;
	int speed;
	int size;
	bool alive;
};

