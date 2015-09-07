#include "GameWorld.h"

#include <iostream>
#include <cmath>
#include <random>

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::init(int width, int height)
{
	std::cout << "Initialize game world params..." << std::endl;
	this->width = width; this->height = height;
	menu_height = 30;
	
	std::cout << "Initialize game menu..." << std::endl;
	int button_w = 70;
	int button_h = 25;
	buttons.push_back(Button(1, width - button_w - 10, 2, button_w, button_h, "Tower 1", [this]() { active_button = 0; }));
	buttons.push_back(Button(2, width - 2 * (button_w + 10), 2, button_w, button_h, "Tower 2", [this]() { active_button = 1; }));
	buttons.push_back(Button(3, width - 3 * (button_w + 10), 2, button_w, button_h, "Tower 3", [this]() { active_button = 2; }));
	buttons.push_back(Button(4, width - 4 * (button_w + 10), 2, button_w, button_h, "Tower 4", [this]() { active_button = 3; }));

	std::cout << "Create goal point..." << std::endl;
	goal_radius = 10;
	goal.x = width - goal_radius * 2;
	goal.y = height / 2;

	resetGame();
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
	if (game_lost) return;

	frame_counter++;
	unsigned int sec = frame_counter / 60;

	if (sec > 0 && frame_counter % 60 == 0 && sec % 10 == 0) createNewWave();

	mapMonsterToTower();
	for (auto tower : towers)
		tower->update();
	std::vector<std::list<std::shared_ptr<BaseMonster>>::iterator> to_remove;
	for (auto it = monsters.begin(); it != monsters.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->update();
			if ((*it)->getPosition().x == goal.x && (*it)->getPosition().y == goal.y)
				game_lost = true;
		}
		else
		{
			money += (*it)->getCost();
			to_remove.push_back(it);
		}
	}
	for (auto it : to_remove) monsters.erase(it);		
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
	if (game_lost) resetGame(); else
	if(y <= menu_height)
		for (Button &b : buttons) Button::press(b, x, y);
	else
	{
		if (active_button > -1 && monsters.size() == 0)
		{
			try {
				auto tower = BaseTower::generaeteTower((BaseTower::TowerTypes)active_button, x, y);
				double test = Point::distance(tower->getPosition(), goal);
				if (x - tower->getRadius() < 0 || x + tower->getRadius() > width) return;
				if (y - tower->getRadius() < 0 || y + tower->getRadius() > height) return;
				if (Point::distance(tower->getPosition(), goal) > width * 0.75) return;
				if (Point::distance(goal, tower->getPosition()) < tower->getRadius() + 30) return;
				double min = width * height * 100;
				int radius = 5;
				for (auto t : towers)
				{
					double dist = Point::distance(tower->getPosition(), t->getPosition());
					if (min > dist) {
						min = dist; radius = t->getRadius();
					}
				}
				if (tower->getRadius() + radius + 30 < min && money >= tower->getCost())
				{
					towers.push_back(tower);
					money -= tower->getCost();
					Point ob = tower->getPosition();
					map.addObstacle(ob, tower->getRadius());
				}
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

void GameWorld::resetGame()
{
	towers.clear();
	monsters.clear();
	map.clear();

	money = 300;
	game_lost = false;

	frame_counter = 0;
	wave_counter = 0;
	active_button = -1;

	std::cout << "Create game map..." << std::endl;
	map.init(width, height, Point(goal.x, goal.y));
	std::cout << "Start game..." << std::endl;
}

void GameWorld::drawMenu()
{
	/*
	Draw MenuBox
	*/
	glBegin(GL_QUADS);	

	glColor3f(0.2,0.2,0.2);
	glVertex2i(0, 0);
	glVertex2i(width , 0);
	glVertex2i(width , menu_height);
	glVertex2i(0, menu_height);

	glEnd();
	/*
	Draw buttons
	*/
	for (Button &b : buttons) b.draw();
	/*
	Write message
	*/
	std::string text = "Total time: " + std::to_string(frame_counter / 60) +
		"; Money: " + std::to_string(money) +
		"; Wave: " + std::to_string(wave_counter);
	int font_x = 20;
	int font_y = (menu_height + 10) / 2;
	glColor3f(1, 1, 1);
	glRasterPos2f(font_x, font_y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.data());

	if (game_lost)
	{
		text = "Looooser!!!!! Left click to start new game.";
		int font_x = (width - glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.data())) / 2;
		int font_y = (height + 10) / 2;
		glColor3f(1, 1, 1);
		glRasterPos2f(font_x, font_y);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.data());
	}
}

void GameWorld::createNewWave()
{
	if (monsters.size() > 0) return;
	wave_counter++;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(menu_height * 2, height - 1);
	int amount = wave_counter;
	int created = 0;
	std::cout << "Generate new wave" << std::endl;
	while (created < amount)
	{
		for (int i = BaseMonster::Simple; i < BaseMonster::End; i++)
		{
			int x = 5;
			int y = dis(gen);
			auto monster = BaseMonster::generateMonster((BaseMonster::MonsterTypes) i, x, y);
			Path p = map.getPath(Point(x, y));
			if (!p.empty())
			{
				monster->setPath(p);
				monsters.push_back(monster);
				created++;
				std::cout << "\tMonster was created (" << x << "; " << y << ")" << std::endl;
				if (created == amount) break;
			}
			else
			{
				std::cout << "\tNo path was find (" << x << "; " << y << ")" << std::endl;
			}
		}
	}
}

void GameWorld::mapMonsterToTower()
{
	for (auto tower : towers)
	{
		double min_dist = width * height * 100;
		std::shared_ptr<BaseMonster> monster;
		for (auto m : monsters)
		{
			if (!m->isAlive()) continue;
			double d = Point::distance(tower->getPosition(), m->getPosition());
			if (d < tower->getRange() && d < min_dist)
			{
				monster = m; min_dist = d;
			}
			if (monster != nullptr) tower->giveBastard(monster);
		}
	}
}
