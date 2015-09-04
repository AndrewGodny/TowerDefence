#pragma once

#include <string>

typedef void(*ButtonCallback)();

class Button
{
public:
	Button(int x, int y, int width, int height, std::string name, ButtonCallback bc);
	~Button();

	static void press(Button &b, int x, int y);
	static void release(Button &b, int x, int y);

	void draw();

private:
	bool clickTest(int x, int y);

private:
	int x, y;
	int width, height;
	bool pressed;
	std::string label;
	ButtonCallback callback;
};

