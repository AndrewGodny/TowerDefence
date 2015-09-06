#include "SpokTower.h"
#include <GL\freeglut.h>


SpokTower::SpokTower(int x, int y): BaseTower(x, y)
{
	range = 150;
	radius = 5;
	damage = 3;
	cost = 700;
}


SpokTower::~SpokTower()
{
}

BaseTower::TowerTypes SpokTower::getType()
{
	return Spok;
}

void SpokTower::draw()
{
	glBegin(GL_QUADS);

	glColor3f(183. / 255, 66. / 255, 189. / 255);
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
