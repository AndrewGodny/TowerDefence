#pragma once

#include <GL\freeglut.h>
#include <vector>

#include "Button.h"

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

	void mousePress(int x, int y);
	void moseRelease(int x, int y);

private:
	void drawMenu();

private:
	int width;
	int height;
	std::vector<Button> buttons;
};

