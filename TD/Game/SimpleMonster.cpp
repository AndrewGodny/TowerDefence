#include "SimpleMonster.h"
#include <GL\freeglut.h>


SimpleMonster::SimpleMonster(int x, int y): BaseMonster(x, y)
{
	hp = 100; speed = 2; size = 5;
}


SimpleMonster::~SimpleMonster()
{
}

void SimpleMonster::update()
{
	position.x += speed;
}

void SimpleMonster::draw()
{
	glBegin(GL_POLYGON);

	glColor3f(216./255, 44./255, 21./255);
	for (double i = 0; i < 2 * M_PI; i += M_PI / 2)
		glVertex2f(cos(i) * size + position.x, sin(i) * size + position.y);

	glEnd();
}

BaseMonster::MonsterTypes SimpleMonster::getType()
{
	return MonsterTypes::Simple;
}
