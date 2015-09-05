#pragma once

#include "../defines.h"

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	void init(int width, int height);

	void addObstacle(Point pos, int radius);

private:
	int width, height;
	std::vector<std::vector<bool>> map;
	std::vector<Path> saved_paths;
};

