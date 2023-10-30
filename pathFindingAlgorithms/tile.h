#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "main.h"

enum Color
{
	NONE, BLUE, LIGHT_BLUE, YELLOW, GREEN, RED, BROWN, PURPLE, WHITE
};

struct Tile
{
	// 0 North and clockwise

	std::vector<Tile*> neighbors = { nullptr, nullptr, nullptr, nullptr };
	std::vector<Tile*> dNeighbors = { nullptr, nullptr, nullptr, nullptr };

	int tileCoordinateX = 0;
	int tileCoordinateY = 0;

	Color color = NONE;

	bool start = false;
	bool end = false;
	bool wall = false;
	bool visited = false;
	Tile* parent = nullptr;

	int r = 230;
	int g = 210;
	int b = 0;
	int a = 255;

	Tile(bool randomizeColors);
	void drawTile(SDL_Renderer* renderer);
	void setColor();
};

int randRangeInclusive(int min, int max);
std::vector<std::vector<Tile>> initializeVector(int X, int Y, bool randomizeColors);
void initializeCoordinates(std::vector<std::vector<Tile>>& arrayMap);
void drawMapArray(SDL_Renderer* renderer, std::vector<std::vector<Tile>>& arrayMap);
void linkMapArray(std::vector<std::vector<Tile>>& arrayMap);