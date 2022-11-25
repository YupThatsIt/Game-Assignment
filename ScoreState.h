#ifndef SCORESTATE_H
#define SCORESTATE_H

#include <fstream>
#include <sstream>

#include "State.h"

class ScoreState : public State
{
private:
	typedef struct Data {
		char name[26];
		int score;
	} Data;
	Data d[6];
	sf::Text leaderboard;
	sf::Text scoreData[5];
	sf::Text back;
	sf::Font font;
	sf::Sprite bg;
	sf::Sound clickSound;
	float clickDelay;
	bool* isEndtoMain;

public:

private:

public:
	ScoreState(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr);
	virtual ~ScoreState();

	void ReadFromFile(Data* d);
	bool isHover(sf::Text* text, sf::Vector2i mousePos);
	void initText(sf::Text* text, std::string words, sf::Vector2f pos, int size, sf::Font& font);
	void Update(float deltaTime); //Definitive virtual function??
	void Render(sf::RenderTarget* target = nullptr);
};

#endif SCORESTATE_H

