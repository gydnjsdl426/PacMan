#include"PacMan.h"

PacMan::PacMan() :Entity(13, 26)
{
	eatenBeans = 0;
}

void PacMan::queueDiretion(Direction dir)
{
	if (!directions.empty())
	{
		if (dir == -directions.front())
		{
			std::queue<Direction> clear;
			std::swap(directions, clear);
		}
	}

	if (directions.size() < 2)
	{
		directions.push(dir);
	}
}

void PacMan::move()
{
	if (!directions.empty())
	{
		switch (directions.front())
		{
		case Direction::up:
			Entity::move(0, -0.5f);
			break;
		case Direction::Down:
			Entity::move(0, 0.5f);
			break;
		case Direction::Left:
			Entity::move(-0.5f, 0);
			break;
		case Direction::Right:
			Entity::move(0.5f, 0);
			break;
		}
	}
}

std::queue<Direction> PacMan::getDirections()
{
	return directions;
}

void PacMan::stop()
{
	if (directions.size() > 1)
	{
		if ((int)(screenPosX + 8) % 16 == 0 && (int)(screenPosY + 8) % 16 == 0)
		{
			directions.pop();
		}
	}
}

void PacMan::eatBean()
{
	eatenBeans++;
}

int PacMan::getBeanEaten()
{
	return eatenBeans;
}

void PacMan::setDead(bool d)
{
	dead = d;
}

bool PacMan::isDead()
{
	return dead;
}

void PacMan::setInvincible(bool i)
{
	if (i)
		invincible = 15000;
	else
		invincible = 0;
}

bool PacMan::isInvincible()
{
	if (invincible > 0)
	{
		invincible--;
	}
	else setInvincible(false);
	return invincible > 0;
}