#pragma once

#include <vector>

#define M_PI 3.14159265358979323846
#define TIME 20
#define SCALE 10

struct Point
{
	int x; int y;

	Point() {}
	Point(int x, int y) : x(x), y(y) {}

	static double distance(const Point& a, const Point& b)
	{
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
};
inline bool operator==(const Point& l, const Point& r) {
	return (l.x == r.x && l.y == r.y);
}

typedef std::vector<Point> Path;