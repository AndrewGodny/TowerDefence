#include "PathFinder.h"
#include <set>

#include "AStar.h"

PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

void PathFinder::init(int width, int height, Point goal)
{
	this->width = width;
	this->height = height;
	this->goal = goal;
	map.reserve(height);
	for (int i = 0; i < height; i++)
	{
		std::vector<bool> arr(width);
		std::fill(arr.begin(), arr.end(), false);
		map.push_back(arr);
	}
}

void PathFinder::addObstacle(Point pos, int radius)
{
	Path check_points;
	map[pos.y][pos.x] = true;
	std::set<std::vector<Path>::iterator> to_remove;
	for (int i = pos.y - radius; i < pos.y + radius; i++)
		for (int j = pos.x - radius; j < pos.x + radius; j++)
			if (i >= 0 && i < height && j >= 0 && j < width)
			{
				map[i][j] = true;
				check_points.push_back(Point(i, j));
				for (auto p = saved_paths.begin(); p != saved_paths.end(); p++)
				{
					Path path = *p;
					if (std::find(path.begin(), path.end(), Point(i, j)) != path.end())
						to_remove.insert(p);
				}
			}
	for (auto it : to_remove) saved_paths.erase(it);
	
}

Path PathFinder::getPath(Point start)
{
	for (Path p : saved_paths)
		if (p[0].x == start.x && p[0].y == start.y)
			return p;
	AStar sp(width, height, map, start, goal);
	Path p = sp.getResult();
	std::reverse(p.begin(), p.end());
	if (!p.empty()) saved_paths.push_back(p);
	return p;
}

void PathFinder::clear()
{
	map.clear();
	width = 0;
	height = 0;
}
