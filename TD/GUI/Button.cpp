#include "Button.h"
#include <GL\freeglut.h>


Button::Button(int id, int x, int y, int width, int height, std::string name, ButtonCallback bc) : 
	id(id),
	x(x), y(y), 
	width(width), height(height), 
	pressed(false), label(name), 
	callback(bc)
{
}


Button::~Button()
{
}

void Button::press(Button & b, int x, int y)
{
	if (b.clickTest(x, y))
	{
		b.pressed = true;
	}
}

void Button::release(Button & b, int x, int y)
{
	if (b.pressed && b.clickTest(x, y))
	{
		if (b.callback) b.callback();
		b.pressed = false;
	}
}

void Button::draw()
{
	/*
	Indicate if button is pressed
	*/
	if (pressed)	glColor3f(0.7, 0.7, 0.8);
	else			glColor3f(0.6, 0.6, 0.6);
	/*
	Draw background for the button
	*/
	glBegin(GL_QUADS);

	glVertex2i(x		, y			);
	glVertex2i(x		, y + height);
	glVertex2i(x + width, y + height);
	glVertex2i(x + width, y			);

	glEnd();
	/*
	Draw outline around the button
	*/
	glLineWidth(3);
	if (pressed)	glColor3f(0.4, 0.4, 0.4);
	else			glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINE_STRIP);

	glVertex2i(x + width, y);
	glVertex2i(x, y);
	glVertex2i(x, y + height);

	glEnd();
	if (pressed)	glColor3f(0.8, 0.8, 0.8);
	else			glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_LINE_STRIP);

	glVertex2i(x, y + height);
	glVertex2i(x + width, y + height);
	glVertex2i(x + width, y);

	glEnd();

	glLineWidth(1);
	/*
	Calculate x and y coords the text string in order to center it
	*/
	int font_x = x + (width - glutBitmapLength(GLUT_BITMAP_8_BY_13, (const unsigned char*)label.data())) / 2;
	int font_y = y + (height + 10) / 2;
	if (pressed) {
		font_x += 2;
		font_y += 2;
	}

	glColor3f(1, 1, 1);
	glRasterPos2f(font_x, font_y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)label.data());
}

bool Button::clickTest(int x, int y)
{
	if (x > this->x && x < this->x + width &&
		y > this->y && y < this->y + height)
		return true;
	return false;
}
