#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <iostream>
#include <stack>

#include "State.h"

class PauseMenu : public State
{
private: //Variables
	sf::Text resumeButton;
	sf::Text Title;
	sf::Text quitButton;
	sf::Font font;
	sf::Sprite bg;
	sf::Sound clickSound;
	float clickDelay;
	bool *isEndtoMain;

public: //Variables

private: //Functions

public: //Functions
	PauseMenu(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr, bool *isEndtoMain);
	virtual ~PauseMenu();

	bool isHover(sf::Text* text, sf::Vector2i mousePos);
	void initText(sf::Text* text, std::string words, sf::Vector2f pos, int size, sf::Font& font);
	void Update(float deltaTime); //Definitive virtual function??
	void Render(sf::RenderTarget* target = nullptr);
};

#endif PAUSEMENU_H

