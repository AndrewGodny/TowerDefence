#include "GameWorld.h"

#include <iostream>

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::init(int width, int height)
{
	this->width = width; this->height = height;

	int button_w = width / 10;
	int button_h = 25;
	buttons.push_back(Button(width - button_w - 10, 2, button_w, button_h, "Tower 1", []() {std::cout << "Mose 1 pressed" << std::endl; }));
	buttons.push_back(Button(width - 2 * (button_w + 10), 2, button_w, button_h, "Tower 2", []() {std::cout << "Mose 2 pressed" << std::endl; }));
	buttons.push_back(Button(width - 3 * (button_w + 10), 2, button_w, button_h, "Tower 3", []() {std::cout << "Mose 3 pressed" << std::endl; }));
	buttons.push_back(Button(width - 4 * (button_w + 10), 2, button_w, button_h, "Tower 4", []() {std::cout << "Mose 4 pressed" << std::endl; }));
}

int GameWorld::getWidth()
{
	return width;
}

int GameWorld::getHeight()
{
	return height;
}

void GameWorld::update()
{
}

void GameWorld::draw()
{
	drawMenu();
}

void GameWorld::mousePress(int x, int y)
{
	for (Button &b : buttons) Button::press(b, x, y);
}

void GameWorld::moseRelease(int x, int y)
{
	for (Button &b : buttons) Button::release(b, x, y);
}

void GameWorld::drawMenu()
{
	int menu_height = 30;
	/*
	Draw MenuBox
	*/
	glBegin(GL_QUADS);

	glColor3f(0.2,0.2,0.2);
	glVertex2i(0, 0);
	glVertex2i(width, 0);
	glVertex2i(width, menu_height);
	glVertex2i(0, menu_height);

	glEnd();
	/*
	Draw buttons
	*/
	for (Button &b : buttons) b.draw();
}
