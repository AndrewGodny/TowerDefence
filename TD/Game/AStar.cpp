#include "AStar.h"
#include <queue>
#include <functional>
#include <iostream>

AStar::AStar(int w, int h, std::vector<std::vector<bool>> m, const Point& start, const Point& finish) : width(w), height(h), map(std::move(m))
{
	open.reserve(height);
	closed.reserve(height);
	direction_map.reserve(height);
	for (int i = 0; i < height; i++)
	{
		std::vector<int> arr(width);
		std::fill(arr.begin(), arr.end(), 0);
		open.push_back(arr);
		closed.push_back(arr);
		direction_map.push_back(arr);
	}

	dx = { 1, 0, -1, 0 };
	dy = { 0, 1, 0, -1 };
	
	auto set_comparer = [](const Node& a, const Node& b) {
		return a.getPriority() > b.getPriority();
	};
	typedef std::priority_queue<Node, std::vector<Node>, bool(*)(const Node&, const Node&)> priority_queue;

	std::vector<priority_queue> pq;
	pq.push_back(priority_queue(set_comparer));
	pq.push_back(priority_queue(set_comparer));
	short pqi = 0;

	Node n0(start.x, start.y, 0, 0);
	n0.updatePriority(finish.x, finish.y);
	pq[pqi].push(n0);
	open[n0.y()][n0.x()] = n0.getPriority();

	while (!pq[pqi].empty())
	{
		Node n = pq[pqi].top();
		pq[pqi].pop();

		int x = n.x(), y = n.y();
		open[y][x] = 0;
		closed[y][x] = 1;
		
		if (finish.x == x && finish.y == y)
		{
			result.push_back(finish);
			while (!(x == start.x && y == start.y))
			{
				int j = direction_map[y][x];
				x += dx[j];
				y += dy[j];
				result.push_back(Point(x, y));
			}		
			while (!pq[pqi].empty())pq[pqi].pop();
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			int xdx = x + dx[i];
			int ydy = y + dy[i];
			if (!(xdx < 0 || xdx > width - 1 ||
				ydy < 0 || ydy > height - 1 ||
				map[ydy][xdx] ||
				closed[ydy][xdx] == 1))
			{
				Node child(xdx, ydy, n.getLevel(), n.getPriority());
				child.nextLevel(i);
				child.updatePriority(finish.x, finish.y);
				if (open[ydy][xdx] == 0)
				{
					open[ydy][xdx] = child.getPriority();
					pq[pqi].push(child);
					direction_map[ydy][xdx] = (i + 2) % 4;
				}
				else if (open[ydy][xdx] > child.getPriority())
				{
					open[ydy][xdx] = child.getPriority();
					direction_map[ydy][xdx] = (i + 2) % 4;
					while (!(pq[pqi].top().x() == xdx || pq[pqi].top().y() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop();
					if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(child);
				}
			}
		}
	}
}


AStar::~AStar()
{
}

Path AStar::getResult()
{
	return result;
}
