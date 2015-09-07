#pragma once

#include "../defines.h"

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	void init(int width, int height, Point goal);

	void addObstacle(Point pos, int original_radius);

	Path getPath(Point start);
	Path adoptPath(const Path& p);

	void clear();

private:
	int width, height;
	Point goal;
	std::vector<std::vector<bool>> map;
	std::vector<Path> saved_paths;
};

