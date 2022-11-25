#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <stack>
#include <memory>

#include "MainMenu.h"
#include "PlayState.h"
#include "ResourceManager.h"
/*
	This class should do - > Update the game input, events and render the display
						 - > Handling game states such as play state mainmenu state pause state
*/

class Game
{
private: //Variables
	sf::RenderWindow* window;
	ResourceManager* resourceManager;
	//sf::Event sfEvent;
	sf::Clock* deltaClock;
	float deltaTime;
	std::stack<State*> state;

public: //Variables

private: //Functions
	void InitWindow();
	void InitResourceManager();
	void Update();
	void Render();

public: //Functions
	Game();
	virtual ~Game();
	void InitState();
	void Run();
};

#endif GAME_H