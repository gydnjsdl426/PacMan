#pragma once

#include"Entity.h"
#include"Directions.h"

class Monster :
	public Entity
{
private:
	int destinationTileX;
	int destinationTileY;
	Direction moving;

	bool scattering;
	bool outOfCage;
	bool decision;

public:
	Monster(int tilePosX, int tilePosY, int destinationX, int destinationY);
	void setDestination(int x, int y);
	int getDestX();
	int getDestY();


	void setDirection(Direction dir);
	Direction getDirection();
	void move();

	bool isScattering();
	void setScattering(bool s);

	bool isOutOfCage();

	bool shouldTakeDecision();
	void setTakeDecision(bool d);

	void teleport(int x, int y);

};