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

void Tile::setColor()
{
	switch (color)
	{
	case RED:
		r = 255;
		g = 0;
		b = 0;
		break;
	case BLUE:
		r = 0;
		b = 255;
		g = 0;
		break;
	case GREEN:
		r = 0;
		g = 255;
		b = 0;
		break;
	case YELLOW:
		r = 255;
		g = 255;
		b = 0;
		break;
	case BROWN:
		r = 128;
		g = 64;
		b = 0;
		break;
	case PURPLE:
		r = 128;
		g = 0;
		b = 255;
		break;
	case LIGHT_BLUE:
		r = 0;
		g = 255;
		b = 255;
		break;
	case WHITE:
		r = 255;
		g = 255;
		b = 255;
		break;
	case NONE:
		r = 0;
		b = 0;
		g = 0;
		break;
	default:
		break;
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

void linkMapArray(std::vector<std::vector<Tile>>& arrayMap)
{
	for (int i = 0; i < arrayMap.size(); ++i) {
		for (int j = 0; j < arrayMap[i].size(); ++j) {

			if (i > 0) {
				(arrayMap[i][j]).neighbors[3] = &arrayMap[i - 1][j];
			}

			if (i < arrayMap.size() - 1) {
				(arrayMap[i][j]).neighbors[1] = &arrayMap[i + 1][j];
			}

			if (j > 0) {
				(arrayMap[i][j]).neighbors[0] = &arrayMap[i][j - 1];
			}

			if (j < arrayMap[1].size() - 1) {
				(arrayMap[i][j]).neighbors[2] = &arrayMap[i][j + 1];
			}
		}
	}

	for (int i = 0; i < arrayMap.size(); ++i) {
		for (int j = 0; j < arrayMap[i].size(); ++j) {

			if (i - 1 >= 0 && j - 1 >= 0) {
				(arrayMap[i][j]).neighbors[3] = &arrayMap[i - 1][j];
			}

			if (i + 1 < arrayMap.size() && j + 1 < arrayMap[i].size()) {
				(arrayMap[i][j]).neighbors[1] = &arrayMap[i + 1][j];
			}

			if (i + 1 < arrayMap.size() && j - 1 >= 0) {
				(arrayMap[i][j]).neighbors[0] = &arrayMap[i][j - 1];
			}

			if (i - 1 >= 0 && j + 1 < arrayMap[1].size()) {
				(arrayMap[i][j]).neighbors[2] = &arrayMap[i][j + 1];
			}
		}
	}
}