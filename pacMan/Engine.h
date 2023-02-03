#pragma once

#include "SFML/Graphics.hpp"
#include "StateManager.h"
#include"Resources.h"

class Engine
{
public:
	sf::RenderWindow window;
	static StateManager gamestates;
	void init(Resources& _r);
	bool isRunning();
	void handleEvents();
	void render();
};