#include "SimpleTower.h"
#include <GL\freeglut.h>


SimpleTower::SimpleTower(int x, int y): BaseTower(x, y)
{
	range = 100;
	radius = 5;
	damage = 1;
	cost = 200;
}


SimpleTower::~SimpleTower()
{
}

BaseTower::TowerTypes SimpleTower::getType()
{
	return TowerTypes::Simple;
}

void SimpleTower::update()
{
	if (bastard != nullptr) {
		if (bastard->isAlive()) bastard->hit(damage);
		if (!bastard->isAlive()) bastard = nullptr;
	}
}

void SimpleTower::draw()
{
	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);
	glVertex2i(position.x - radius, position.y - radius);
	glVertex2i(position.x + radius, position.y - radius);
	glVertex2i(position.x + radius, position.y + radius);
	glVertex2i(position.x - radius, position.y + radius);

	glEnd();

	glBegin(GL_LINE_LOOP);

	for (double i = 0; i < 2 * M_PI; i += M_PI / 20)
		glVertex2f(cos(i) * range + position.x, sin(i) * range + position.y);

	glEnd();

	if (bastard != nullptr)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2i(position.x, position.y);
		glVertex2i(bastard->getPosition().x, bastard->getPosition().y);
		glEnd();
	}
}
