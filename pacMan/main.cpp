#include "Engine.h"
#include "SFML/Graphics.hpp"
#include "StateManager.h"
#include"Resources.h"

using namespace sf;


int main() 
{
	srand((unsigned int)time(NULL));
	Resources r;
	Engine e;
	e.init(r);
	while (e.isRunning())
	{
		e.handleEvents();
		e.render();
	}

	return 0;
}