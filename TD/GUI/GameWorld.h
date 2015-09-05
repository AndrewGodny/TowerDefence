#pragma once

#include <GL\freeglut.h>
#include <vector>
#include <list>

#include "Button.h"
#include "../Game/BaseTower.h"
#include "../Game/BaseMonster.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void init(int width, int height);
	int getWidth();
	int getHeight();

	void update();
	void draw();

	void mouseLeftClickPress(int x, int y);
	void moseLeftClickRelease(int x, int y);
	void mouseRightClickPress(int x, int y);

private:
	void drawMenu();

private:
	/*
	Window params and some GUI consfigs
	*/
	int width;
	int height;
	int menu_height;

	Point goal;
	int goal_radius;

	int active_button;
	
	std::vector<Button> buttons;
	std::list<std::shared_ptr<BaseTower>> towers;
	std::list<std::shared_ptr<BaseMonster>> monsters;
};

