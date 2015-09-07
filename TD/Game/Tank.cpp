#include "Tank.h"
#include <GL\freeglut.h>


TankMonster::TankMonster(int x, int y): BaseMonster(x, y)
{
	hp = 600; speed = 1; size = 5; cost = 300;
}


TankMonster::~TankMonster()
{
}

void TankMonster::draw()
{
	glBegin(GL_POLYGON);

	glColor3f(30. / 255, 30. / 255, 50. / 255);
	for (double i = 0; i < 2 * M_PI; i += M_PI / 2)
		glVertex2f(cos(i) * size + position.x, sin(i) * size + position.y);

	glEnd();
}

BaseMonster::MonsterTypes TankMonster::getType()
{
	return Tank;
}
