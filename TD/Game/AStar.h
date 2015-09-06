#pragma once

#include "../defines.h"

class AStar
{
public:
	AStar(int w, int h, std::vector<std::vector<bool>> m, const Point& start, const Point& finish);
	~AStar();

	Path getResult();

private:
	class Node
	{
	public:
		Node(int xp, int yp, int l, int p) : x_pos(xp), y_pos(yp), level(l), priority(p) { }
		
		int x() const { return x_pos; }
		int y() const { return y_pos; }
		int getLevel() const { return level; }
		int getPriority() const { return priority; }

		void updatePriority(int xDest, int yDest)
		{
			int dist = Point::distance(Point(x_pos, y_pos), Point(xDest, yDest));
			priority = level + dist * 10;
		}

		void nextLevel(int direction)
		{
			level += 10;
		}

	private:
		int x_pos, y_pos, level, priority;
	};

private:
	int width, height;
	std::vector<std::vector<bool>> map;
	std::vector<std::vector<int>> open;
	std::vector<std::vector<int>> closed;
	std::vector<std::vector<int>> direction_map;
	std::vector<int> dx, dy;
	Path result;
};

