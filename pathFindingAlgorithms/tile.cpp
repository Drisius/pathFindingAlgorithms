#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "tile.h"
#include "main.h"

Tile::Tile(bool randomizeColors)
{
	if (randomizeColors) {
		r = randRangeInclusive(0, 255);
		g = randRangeInclusive(0, 255);
		b = randRangeInclusive(0, 255);
	}
}

void Tile::drawTile(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	for (int i = 0; i < SPRITE_SIZE; ++i) {
		for (int j = 0; j < SPRITE_SIZE; ++j) {
			SDL_RenderDrawPoint(renderer, tileCoordinateX + i, tileCoordinateY + j);
		}
	}
}

std::vector<std::vector<Tile>> initializeVector(int X, int Y, bool randomizeColors)
{
	std::vector<std::vector<Tile>> tempX;

	for (int i = 0; i < X; ++i) {
		std::vector<Tile> tempY;
		for (int j = 0; j < Y; ++j) {
			Tile t(randomizeColors);
			tempY.push_back(t);
		}
		tempX.push_back(tempY);
	}

	return tempX;
}

int randRangeInclusive(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void initializeCoordinates(std::vector<std::vector<Tile>>& arrayMap)
{
	for (int i = 0; i < arrayMap.size(); ++i) {
		for (int j = 0; j < arrayMap[i].size(); ++j) {
			(arrayMap[i][j]).tileCoordinateX = i * SPRITE_SIZE;
			(arrayMap[i][j]).tileCoordinateY = j * SPRITE_SIZE;
		}
	}
}

void drawMapArray(SDL_Renderer* renderer, std::vector<std::vector<Tile>>& arrayMap)
{
	for (int i = 0; i < arrayMap.size(); ++i) {
		for (int j = 0; j < arrayMap[i].size(); ++j) {
			(arrayMap[i][j]).drawTile(renderer);
		}
	}
}