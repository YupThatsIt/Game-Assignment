#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <stack>

#include "State.h"
#include "PlayState.h"
#include "ScoreState.h"

class MainMenu : public State
{
private: //Variables
	sf::Text playButton;
	sf::Text Title;
	sf::Text quitButton;
	sf::Text leaderBoardButton;
	sf::Text name;
	sf::Font font;
	sf::Sprite bg;
	sf::Sound clickSound;
	sf::Music mainMenuTheme;
	//sf::Music
	float clickDelay;
	bool resumeMusic;

public: //Variables

private: //Functions

public: //Functions
	MainMenu(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr);
	virtual ~MainMenu();

	bool isHover(sf::Text* text, sf::Vector2i mousePos);
	void initText(sf::Text* text, std::string words, sf::Vector2f pos, int size, sf::Font& font);
	void ToNextState(int stateNum);
	void Update(float deltaTime); //Definitive virtual function??
	void Render(sf::RenderTarget* target = nullptr);
};

#endif MAINMENU_H
