#pragma once

#define M_PI 3.14159265358979323846

struct Point
{
	int x; int y;
	static double distance(const Point& a, const Point& b)
	{
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
};