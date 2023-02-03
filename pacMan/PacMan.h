#pragma once
#include"Entity.h"
#include<queue>
#include"Directions.h"

class PacMan : public Entity
{
private:
	std::queue<Direction> directions;
	int eatenBeans;
	bool dead;
	int invincible;

public:
	PacMan();
	void queueDiretion(Direction dir);
	void move();
	std::queue<Direction> getDirections();
	void stop();

	void eatBean();
	int getBeanEaten();

	void setDead(bool d);
	bool isDead();

	void setInvincible(bool i);
	bool isInvincible();
};