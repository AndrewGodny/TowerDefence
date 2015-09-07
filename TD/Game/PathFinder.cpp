#include "PathFinder.h"
#include <set>

#include "AStar.h"

#define SCALE 10

PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

void PathFinder::init(int width, int height, Point goal)
{
	this->width = width / SCALE;
	this->height = height / SCALE;
	this->goal = goal;
	this->goal.x /= SCALE;
	this->goal.y /= SCALE;
	map.reserve(this->height);
	for (int i = 0; i < this->height; i++)
	{
		std::vector<bool> arr(this->width);
		std::fill(arr.begin(), arr.end(), false);
		map.push_back(arr);
	}
}
#include<iostream>
void PathFinder::addObstacle(Point pos, int original_radius)
{
	pos.x /= SCALE; pos.y /= SCALE; 
	int radius = original_radius / SCALE;
	std::set<std::vector<Path>::iterator> to_remove;
	
	for (int i = pos.y - radius; i <= pos.y + radius; i++)
		for (int j = pos.x - radius; j <= pos.x + radius; j++)
			if (i >= 0 && i < height && j >= 0 && j < width)
			{
				map[i][j] = true;
				for (auto p = saved_paths.begin(); p != saved_paths.end(); p++)
				{
					Path path = *p;
					for (Point point : path)
					{
						Point cur, next;
						next.x = pos.x * SCALE; next.y = pos.y * SCALE;
						double d = Point::distance(point, next);
						if (Point::distance(point, next) <= original_radius)
							to_remove.insert(p);
					}
				}
			}
	for (auto it : to_remove)
	{
		std::cout << "Remove path" << std::endl;
		saved_paths.erase(it);
	}
	
}

Path PathFinder::getPath(Point start)
{
	start.x /= SCALE; start.y /= SCALE;
	for (Path p : saved_paths)
		if (p[0].x == start.x && p[0].y == start.y)
			return p;
	AStar sp(width, height, map, start, goal);
	Path p = sp.getResult();
	std::reverse(p.begin(), p.end());
	if (!p.empty())
	{
		p = adoptPath(p);
		saved_paths.push_back(p);
	}
	return p;
}

Path PathFinder::adoptPath(const Path & p)
{
	Path path;
	Point cur, next;
	for (int i = 0; i < p.size() - 1; i++)
	{
		cur.x = p[i].x * SCALE; cur.y = p[i].y * SCALE;
		next.x = p[i + 1].x * SCALE; next.y = p[i + 1].y * SCALE;
		path.push_back(cur);
		int dx = (next.x - cur.x) / SCALE;
		int dy = (next.y - cur.y) / SCALE;
		while (!(cur.x == next.x && cur.y == next.y))
		{
			cur.x = cur.x + dx;
			cur.y = cur.y + dy;
			path.push_back(cur);
		}
	}
	path.push_back(next);
	return path;
}

void PathFinder::clear()
{
	map.clear();
	width = 0;
	height = 0;
}
