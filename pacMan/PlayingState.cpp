#include"PlayingState.h"
#include"Entity.h"
#include"PacMan.h"

PlayingState::PlayingState()
{
	buffer.loadFromFile("car-door-closewav-6929.wav");
	sound.setBuffer(buffer);
}

void PlayingState::init()
{
	labyrinth = new Labyrinth();
	pacman = new PacMan();
	blinky = new Monster(13, 14, 3, 4);
	pinky = new Monster(13, 17, 23, 4);
	inky = new Monster(11, 17, 26, 32);
	clyde = new Monster(15, 17, 1, 32);

	blinky->teleport(13, 14);
	srand(time(NULL));
	waitTime = 0;
}

void PlayingState::loop()
{
	if (canPacmanMove() && !pacman->isDead())
	{
		pacman->move();
	}
	else
	{
		pacman->stop();
	}
	if (labyrinth->isIntersection(pacman->getTileX(), pacman->getTileY()))
	{
		pacman->stop();
	}
	labyrinth->removeBean(pacman);

	if (!pacman->getDirections().empty())
	{
		if (!blinky->isScattering())
			blinky->setDestination(pacman->getTileX(), pacman->getTileY()); // 팩맨의 위치로 destination 설정

		if (!pinky->isScattering()) // destination에 도달 했으면
		{
			switch (pacman->getDirections().front())
			{
			case Direction::up:
				pinky->setDestination(pacman->getTileX(), pacman->getTileY() - 4);
				break;
			case Direction::Down:
				pinky->setDestination(pacman->getTileX(), pacman->getTileY() + 4);
				break;
			case Direction::Left:
				pinky->setDestination(pacman->getTileX() - 4, pacman->getTileY());
				break;
			case Direction::Right:
				pinky->setDestination(pacman->getTileX() + 4, pacman->getTileY());
				break;
			}
		}

		if (!inky->isScattering())
			inky->setDestination(pacman->getTileX() + (blinky->getTileX() - pacman->getTileX()), pacman->getTileY() + (blinky->getTileY() - pacman->getTileY()));

		if (!clyde->isScattering())
		{
			if (sqrt(pow((clyde->getTileX() - (pacman->getTileX())), 2) + pow((clyde->getTileY() - (pacman->getTileY())), 2)) < 9)
			{
				clyde->setDestination(pacman->getTileX(), pacman->getTileY());
			}
			else
			{
				clyde->setDestination(1, 32);
			}
		}
	}

	handleMonsterMovemnet(blinky);
	handleMonsterMovemnet(pinky);
	handleMonsterMovemnet(inky);
	handleMonsterMovemnet(clyde);

	if (pacman->getBeanEaten() == 5)
		pinky->teleport(13, 14);
	if (pacman->getBeanEaten() == 50)
		inky->teleport(13, 14);
	if (pacman->getBeanEaten() == 100)
		clyde->teleport(13, 14);

	teleportTunnels(pacman);
	teleportTunnels(blinky);
	teleportTunnels(pinky);
	teleportTunnels(inky);
	teleportTunnels(clyde);

	isPacmanCaught(blinky);
	isPacmanCaught(pinky);
	isPacmanCaught(inky);
	isPacmanCaught(clyde);

	if (pacman->getBeanEaten() == 243)
	{
		blinky->teleport(-2, -2);
		pinky->teleport(-2, -2);
		inky->teleport(-2, -2);
		clyde->teleport(-2, -2);
		waitTime++;
	}

	if (pacman->isDead())
		waitTime++;

	if (waitTime == 200)
	{
		if (pacman->isDead())
		{
			if (blinky->isOutOfCage()) blinky->teleport(13, 14);
			if (pinky->isOutOfCage()) pinky->teleport(13, 14);
			if (inky->isOutOfCage()) inky->teleport(13, 14);
			if (clyde->isOutOfCage()) clyde->teleport(13, 14);
			pacman->teleport(13, 26);
			pacman->setDead(false);
			waitTime = 0;
		}
		else
		{
			clearedStages++;
			Entity::level = 0.0001f * clearedStages;
			labyrinth->makeItem();
			PlayingState::init();
			waitTime = 0;
		}
	}
}

void PlayingState::render(RenderWindow* window)
{
	Sprite pacmanSprite;
	Sprite blinkySprite;
	Sprite pinkySprite;
	Sprite inkySprite;
	Sprite clydeSprite;

	if (pacman->getDirections().empty())
		pacmanSprite = *Resources::get(Resources::PacMan, false, Direction::Unset);
	else
		pacmanSprite = *Resources::get(Resources::PacMan, true, pacman->getDirections().front());

	if (pacman->isDead()) {
		pacmanSprite = *Resources::get(Resources::DeadPacMan, true, Direction::Unset);
	}

	if (pacman->isInvincible())
	{
		pacmanSprite.setColor(Color::Green);
		pacmanSprite.setScale(3.0f, 3.0f);
	}

	blinkySprite = *Resources::get(Resources::Blinky, blinky->isOutOfCage(), blinky->getDirection());
	pinkySprite = *Resources::get(Resources::Pinky, pinky->isOutOfCage(), pinky->getDirection());
	inkySprite = *Resources::get(Resources::Inky, inky->isOutOfCage(), inky->getDirection());
	clydeSprite = *Resources::get(Resources::Clyde, clyde->isOutOfCage(), clyde->getDirection());

	pacmanSprite.setPosition(pacman->getScreenPosX(), pacman->getScreenPosY());
	blinkySprite.setPosition(blinky->getScreenPosX(), blinky->getScreenPosY());
	pinkySprite.setPosition(pinky->getScreenPosX(), pinky->getScreenPosY());
	inkySprite.setPosition(inky->getScreenPosX(), inky->getScreenPosY());
	clydeSprite.setPosition(clyde->getScreenPosX(), clyde->getScreenPosY());

	for (int i = 0; i < Labyrinth::SizeX; i++)
	{
		for (int j = 0; j < Labyrinth::SizeY; j++)
		{
			Resources::LabyrinthPieces[labyrinth->getTileCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
			window->draw(*Resources::LabyrinthPieces[labyrinth->getTileCode(i, j)]);
		}
	}

	window->draw(pacmanSprite);
	window->draw(blinkySprite);
	window->draw(pinkySprite);
	window->draw(inkySprite);
	window->draw(clydeSprite);
}

void PlayingState::keyPressed(int code)
{
	switch (code)
	{
	case Keyboard::Up:
		pacman->queueDiretion(Direction::up);
		break;
	case Keyboard::Down:
		pacman->queueDiretion(Direction::Down);
		break;
	case Keyboard::Left:
		pacman->queueDiretion(Direction::Left);
		break;
	case Keyboard::Right:
		pacman->queueDiretion(Direction::Right);
		break;
	}
}

void PlayingState::keyReleased(int code)
{

}

bool PlayingState::canPacmanMove()
{
	if (!pacman->getDirections().empty())
	{
		switch (pacman->getDirections().front())
		{
		case Direction::up:
			return !labyrinth->tileBlocksEntity(pacman->getTileX(), pacman->getTileY() - 1);
			break;
		case Direction::Down:
			return !labyrinth->tileBlocksEntity(pacman->getTileX(), pacman->getTileY() + 1);
			break;
		case Direction::Left:
			return !labyrinth->tileBlocksEntity(pacman->getTileX() - 1, pacman->getTileY());
			break;
		case Direction::Right:
			return !labyrinth->tileBlocksEntity(pacman->getTileX() + 1, pacman->getTileY());
			break;
		}
	}
	return true;
}

void PlayingState::handleMonsterMovemnet(Monster* monster)
{
	if (monster->isScattering())
	{
		if (monster->getTileX() == monster->getDestX() && monster->getTileY() == monster->getDestY())
		{
			monster->setScattering(false);
		}
	}

	if (labyrinth->isIntersection(monster->getTileX(), monster->getTileY()))
	{
		if (monster->shouldTakeDecision())
		{
			float dRight = calculateDistance(monster, 1, 0);
			float dLeft = calculateDistance(monster, -1, 0);
			float dUp = calculateDistance(monster, 0, -1);
			float dDown = calculateDistance(monster, 0, 1);

			if (dRight < dLeft && dRight < dUp && dRight < dDown)
			{
				monster->setDirection(Direction::Right);
			}
			else if (dLeft < dRight && dLeft < dUp&&dLeft < dDown)
			{
				monster->setDirection(Direction::Left);
			}
			else if (dUp < dRight&& dUp < dLeft&&dUp < dDown)
			{
				monster->setDirection(Direction::up);
			}
			else if (dDown < dLeft && dDown < dRight && dDown < dUp)
			{
				monster->setDirection(Direction::Down);
			}
		}
		monster->setTakeDecision(false);
	}
	else
	{
		monster->setTakeDecision(true);
	}
	
	if (canMonsterMove(monster) && monster->isOutOfCage())
	{
		monster->move();
	}
	else
	{
		monster->setTakeDecision(true);
	}
}

bool PlayingState::canMonsterMove(Monster* monster)
{
	switch (monster->getDirection())
	{
	case Direction::up:
		return !labyrinth->tileBlocksEntity(monster->getTileX(), monster->getTileY() - 1);
		break;
	case Direction::Down:
		return !labyrinth->tileBlocksEntity(monster->getTileX(), monster->getTileY() + 1);
		break;
	case Direction::Left:
		return !labyrinth->tileBlocksEntity(monster->getTileX() - 1, monster->getTileY());
		break;
	case Direction::Right:
		return !labyrinth->tileBlocksEntity(monster->getTileX() + 1, monster->getTileY());
		break;
	}
	return true;
}

void PlayingState::teleportTunnels(Entity* entity)
{
	if (entity->getTileX() == 0 && entity->getTileY() == 17)
		entity->teleport(26, 17);
	else if (entity->getTileX() == 27 && entity->getTileY() == 17)
		entity->teleport(1, 17);
}

float PlayingState::calculateDistance(Monster* monster, int addX, int addY)
{
	float distance = 1000000.0f;
	if (!labyrinth->tileBlocksEntity(monster->getTileX() + addX, monster->getTileY() + addY))
	{
		distance = (float)sqrt(pow((monster->getDestX() - (monster->getTileX() + addX)), 2) + pow((monster->getDestY() - (monster->getTileY() + addY)), 2));
	}
	return distance;
}

void PlayingState::isPacmanCaught(Monster* monster)
{
	if (!pacman->isInvincible() && pacman->getTileX() == monster->getTileX() && pacman->getTileY() == monster->getTileY())
	{
		sound.play();
		pacman->setDead(true);
		blinky->teleport(-2, -2);
		pinky->teleport(-2, -2);
		inky->teleport(-2, -2);
		clyde->teleport(-2, -2);
	}
}