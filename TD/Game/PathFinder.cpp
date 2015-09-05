#include "PathFinder.h"
#include <iostream>
#include <fstream>


PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

void PathFinder::init(int width, int height)
{
	this->width = width;
	this->height = height;
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
	for (int i = pos.y - radius; i < pos.y + radius; i++)
		for (int j = pos.x - radius; j < pos.x + radius; j++)
			if (i >= 0 && i < height && j >= 0 && j < width)
			{
				map[i][j] = true;
			}
	/*std::cout << "Obstacle: " << pos.x << "; " << pos.y << " radius: " << radius << std::endl;
	std::ofstream file;
	file.open("test.txt");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			file << map[i][j] << " ";
		file << std::endl;
	}
	file.close();*/
}
