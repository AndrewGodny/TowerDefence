#include "SimpleMonster.h"
#include <GL\freeglut.h>


SimpleMonster::SimpleMonster(int x, int y): BaseMonster(x, y)
{
	hp = 80; speed = 2; size = 5; cost = 100;
}


SimpleMonster::~SimpleMonster()
{
}

void SimpleMonster::update()
{
	for (int i = 0; i < speed; i++)
	{
		if (i >= path.size()) break;
		position.x = path[0].x;
		position.y = path[0].y;
		path.erase(path.begin());
	}	
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
