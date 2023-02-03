#include"Monster.h"

Monster::Monster(int tilePosX, int tilePosY, int destinationX, int destinationY) : Entity(tilePosX, tilePosY)
{
	setDestination(destinationX, destinationY);
	setDirection(Direction::Unset);
	scattering = true;
	outOfCage = false;
	decision = true;
}

void Monster::setDestination(int x, int y)
{
	destinationTileX = x;
	destinationTileY = y;
}

int Monster::getDestX()
{
	return destinationTileX;
}

int Monster::getDestY()
{
	return destinationTileY;
}

void Monster::setDirection(Direction dir)
{
	moving = dir;
}

Direction Monster::getDirection()
{
	return moving;
}

bool Monster::isScattering()
{
	return scattering;
}

void Monster::setScattering(bool s)
{
	scattering = s;
}

bool Monster::isOutOfCage()
{
	return outOfCage;
}

bool Monster::shouldTakeDecision()
{
	return decision;
}

void Monster::setTakeDecision(bool d)
{
	decision = d;
}

void Monster::move()
{
	if (level <= 0.25f)
	{
		level += 0.000005f;
	}
	switch (moving)
	{
	case Direction::up:
		Entity::move(0, -0.2f - level);
		break;
	case Direction::Down:
		Entity::move(0, 0.2f + level);
		break;
	case Direction::Left:
		Entity::move(-0.2 - level, 0);
		break;
	case Direction::Right:
		Entity::move(0.2f + level, 0);
		break;
	}
}

void Monster::teleport(int x, int y)
{
	Entity::teleport(x, y);
	outOfCage = true;
}