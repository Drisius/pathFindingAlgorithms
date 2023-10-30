#include <vector>
#include <deque>
#include <iostream>
#include <Windows.h>

#include "main.h"
#include "tile.h"
#include "algorithms.h"

void setStart(std::vector<std::vector<Tile>>& map)
{
	int xStart = randRangeInclusive(0, X_DIMENSION - 1);
	int yStart = randRangeInclusive(0, Y_DIMENSION - 1);

	map[xStart][yStart].start = true;
	map[xStart][yStart].color = GREEN;
	map[xStart][yStart].setColor();
}

void setEnd(std::vector<std::vector<Tile>>& map)
{
	int xStart = randRangeInclusive(0, X_DIMENSION - 1);
	int yStart = randRangeInclusive(0, Y_DIMENSION - 1);

	while (map[xStart][yStart].start) {
		xStart = randRangeInclusive(0, X_DIMENSION - 1);
		yStart = randRangeInclusive(0, Y_DIMENSION - 1);
	}

	map[xStart][yStart].end = true;
	map[xStart][yStart].color = PURPLE;
	map[xStart][yStart].setColor();
}

// Breadth-first search along the two axises
void breadthFirstStraightSearch(std::vector<std::vector<Tile>>& map)
{
	std::deque<Tile*> queue;
	bool endFound = false;
	Tile* endPoint = nullptr;

	for (int x = 0; x < X_DIMENSION; ++x) {
		for (int y = 0; y < Y_DIMENSION; ++y) {
			if (map[x][y].start) {
				queue.push_back(&map[x][y]);
				map[x][y].visited = true;
			}
		}
	}

	while (queue.size() != 0 && !endFound) {
		for (int i = 0; i < 4; ++i) {
			Tile* currentNeighbor = queue[0]->neighbors[i];
			if (currentNeighbor != nullptr && !currentNeighbor->visited) {
				OutputDebugStringA("NEIGHBOR ADDED.");
				currentNeighbor->visited = true;
				currentNeighbor->parent = queue[0];
				queue.push_back(currentNeighbor);

				if (currentNeighbor->end) {
					OutputDebugStringA("END FOUND.");
					endFound = true;
					endPoint = currentNeighbor->parent;
					break;
				}
			}
		}
		queue.pop_front();
	}

	while (!endPoint->start) {
		endPoint->color = BLUE;
		endPoint->setColor();
		endPoint = endPoint->parent;
	}
}