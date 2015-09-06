#include "WideRangeTower.h"
#include <GL\freeglut.h>


WideRangeTower::WideRangeTower(int x, int y): BaseTower(x, y)
{
	range = 200;
	radius = 5;
	damage = 1;
	cost = 200;
}


WideRangeTower::~WideRangeTower()
{
}

BaseTower::TowerTypes WideRangeTower::getType()
{
	return WideRange;
}

void WideRangeTower::draw()
{
	glBegin(GL_QUADS);

	glColor3f(66./255, 66./255, 188./255);
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
