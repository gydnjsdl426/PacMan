#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"GameState.h"
#include"Resources.h"
#include"Directions.h"
#include"Labyrinth.h"
#include"PacMan.h"
#include"Monster.h"
#include"Entity.h"

#include <cmath>
#include <random>
#include <cstdlib>

using namespace sf;

class PlayingState :
	public GameState
{
private:
	Labyrinth* labyrinth;
	PacMan* pacman;
	Monster* blinky;
	Monster* pinky;
	Monster* inky;
	Monster* clyde;

	int waitTime;
	int clearedStages = 0;

	bool canPacmanMove();
	void handleMonsterMovemnet(Monster* monster);
	float calculateDistance(Monster* monster, int addX, int addY);
	bool canMonsterMove(Monster* monster);
	void teleportTunnels(Entity* entity);
	void isPacmanCaught(Monster* monster);

public:
	void init();
	void loop();
	void render(sf::RenderWindow* window);
	void keyPressed(int code);
	void keyReleased(int code);

	SoundBuffer buffer;
	Sound sound;
	PlayingState();
};