#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>

#include "ResourceManager.h"

#include <iostream>

class State
{
protected:
	ResourceManager* resourceManager;
	sf::RenderWindow* window;
	std::stack<State*>* statesPtr;
	sf::View* view;

private: //Variables
	bool isEnd;

public: //Variables

private: //Functions
	
public: //Functions
	State(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr);
	virtual ~State();

	const bool &GetIsEnd() const;
	virtual void SetIsEnd(bool isend);

	virtual void EndState();
	virtual void Update(float deltaTime) = 0; //Definitive virtual function??
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;
};

#endif STATE_H

