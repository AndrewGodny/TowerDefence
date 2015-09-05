#pragma once

#include <string>
#include <functional>

typedef std::function<void(void)> ButtonCallback;

class Button
{
public:
	Button(int id, int x, int y, int width, int height, std::string name, ButtonCallback bc);
	~Button();

	static void press(Button &b, int x, int y);
	static void release(Button &b, int x, int y);

	void draw();

private:
	bool clickTest(int x, int y);

private:
	int id;
	int x, y;
	int width, height;
	bool pressed;
	std::string label;
	ButtonCallback callback;
};

