#pragma once

#include<vector>
#include"PacMan.h"
#include"Monster.h"

class Labyrinth
{
public:
	static const int SizeX = 28;
	static const int SizeY = 36;

	Labyrinth();

	int getTileCode(int x, int y);
	bool tileBlocksEntity(int x, int y);
	bool isIntersection(int x, int y);

	void removeBean(PacMan* pacman);

	void makeItem();
	std::vector<int> beanX;
	std::vector<int> beanY;
	int itemIdx = -1;

private:
	int tiles[SizeX][SizeY];
};
