#include "Halk.h"
#include <GL\freeglut.h>


HalkTower::HalkTower(int x, int y): BaseTower(x, y)
{
	range = 50;
	radius = 5;
	damage = 10;
	cost = 1000;
}


HalkTower::~HalkTower()
{
}

BaseTower::TowerTypes HalkTower::getType()
{
	return TowerTypes();
}

void HalkTower::draw()
{
	glBegin(GL_QUADS);

	glColor3f(214. / 255, 240. / 255, 8. / 255);
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
