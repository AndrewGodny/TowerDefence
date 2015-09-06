#include "BaseMonster.h"
#include "SimpleMonster.h"
#include "QuickMonster.h"
#include "Tank.h"

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

int BaseMonster::getCost()
{
	return cost;
}

bool BaseMonster::isAlive()
{
	return alive;
}

void BaseMonster::setPath(Path p)
{
	Point cur, next;
	for (int i = 0; i < p.size() - 1; i++)
	{		
		cur.x = p[i].x * SCALE; cur.y = p[i].y * SCALE;
		next.x = p[i + 1].x * SCALE; next.y = p[i + 1].y * SCALE;
		path.push_back(cur);
		int dx = (next.x - cur.x) / SCALE;
		int dy = (next.y - cur.y) / SCALE;
		while(!(cur.x == next.x && cur.y == next.y))
		{
			cur.x = cur.x + dx;
			cur.y = cur.y + dy;
			path.push_back(cur);
		}
	}
	path.push_back(next);
}

void BaseMonster::hit(int damage)
{
	if (!alive) return;
	hp -= damage;
	if (hp <= 0) alive = false;
}

BaseMonster::BaseMonster(int x, int y)
{
	position.x = x;
	position.y = y;
	speed = 0; hp = 100;
	size = 5;
	alive = true;
}


std::shared_ptr<BaseMonster> BaseMonster::generateMonster(MonsterTypes type, int x, int y)
{
	switch (type)
	{
	case BaseMonster::Simple:
		return std::shared_ptr<SimpleMonster>(new SimpleMonster(x, y));
	case BaseMonster::Quick:
		return std::shared_ptr<QuickMonster>(new QuickMonster(x, y));
	case BaseMonster::Tank:
		return std::shared_ptr<TankMonster>(new TankMonster(x, y));
	default:
		throw std::exception("Undefined tower type");
	}
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::update()
{
	for (int i = 0; i < speed; i++)
	{
		if (i >= path.size()) break;
		position.x = path[0].x;
		position.y = path[0].y;
		path.erase(path.begin());
	}
}
