#include "GameWorld.h"

#include <iostream>
#include <cmath>

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::init(int width, int height)
{
	this->width = width; this->height = height;
	menu_height = 30;
	active_button = -1;

	int button_w = width / 10;
	int button_h = 25;
	buttons.push_back(Button(1, width - button_w - 10, 2, button_w, button_h, "Tower 1", [this]() { active_button = 0; }));
	buttons.push_back(Button(2, width - 2 * (button_w + 10), 2, button_w, button_h, "Tower 2", [this]() { active_button = 1; }));
	buttons.push_back(Button(3, width - 3 * (button_w + 10), 2, button_w, button_h, "Tower 3", [this]() { active_button = 2; }));
	buttons.push_back(Button(4, width - 4 * (button_w + 10), 2, button_w, button_h, "Tower 4", [this]() { active_button = 3; }));

	goal.x = width - 20;
	goal.y = height / 2;
	goal_radius = 10;

	monsters.push_back(BaseMonster::generateMonster((BaseMonster::MonsterTypes) 0, 20, height / 2));
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
	for (auto tower : towers)
		tower->update();
	for (auto monster : monsters)
		monster->update();
}

void GameWorld::draw()
{
	/*
	Draw Goal point
	*/
	glBegin(GL_POLYGON);

	for (double i = 0; i < 2 * M_PI; i += M_PI / 12)
		glVertex2f(cos(i) * goal_radius + goal.x, sin(i) * goal_radius + goal.y);

	glEnd();
	/*
	Draw Towers and Monsters
	*/
	for (auto tower : towers)
		tower->draw();
	for (auto monster : monsters)
		monster->draw();

	drawMenu();
}

void GameWorld::mouseLeftClickPress(int x, int y)
{
	if(y <= menu_height)
		for (Button &b : buttons) Button::press(b, x, y);
	else
	{
		if (active_button > -1)
		{
			try {
				auto tower = BaseTower::generaeteTower((BaseTower::TowerTypes)active_button, x, y);
				double min = width * height;
				int radius = 5;
				for (auto t : towers)
				{
					double dist = Point::distance(tower->getPosition(), t->getPosition());
					if (min > dist) {
						min = dist; radius = t->getRadius();
					}
				}
				if (tower->getRadius() + radius + 10 < min)
					towers.push_back(tower);
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
}

void GameWorld::moseLeftClickRelease(int x, int y)
{
	for (Button &b : buttons) Button::release(b, x, y);
}

void GameWorld::mouseRightClickPress(int x, int y)
{
	active_button = -1;
}

void GameWorld::drawMenu()
{
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
