#include "QuickMonster.h"
#include <GL\freeglut.h>


QuickMonster::QuickMonster(int x, int y): BaseMonster(x, y)
{
	hp = 100; speed = 5; size = 5; cost = 150;
}


QuickMonster::~QuickMonster()
{
}

void QuickMonster::draw()
{
	glBegin(GL_POLYGON);

	glColor3f(36. / 255, 234. / 255, 189. / 255);
	for (double i = 0; i < 2 * M_PI; i += M_PI / 2)
		glVertex2f(cos(i) * size + position.x, sin(i) * size + position.y);

	glEnd();
}

BaseMonster::MonsterTypes QuickMonster::getType()
{
	return Quick;
}
