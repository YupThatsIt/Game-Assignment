#include "ScoreState.h"

ScoreState::ScoreState(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr) : State(window, resourceManager, statesPtr)
{
	this->resourceManager = resourceManager;
	this->clickDelay = 0.f;
	//this->isEndtoMain = isEndtoMain;
	this->view->setCenter(sf::Vector2f(960.f, 540.f));
	this->clickSound.setBuffer(this->resourceManager->getSoundBuffer("ButtonClick"));

	ReadFromFile(d);

	font = resourceManager->getFont("ZombieQueen");

	this->bg.setTexture(this->resourceManager->getTexture("LeaderboardBG"));

	initText(&leaderboard, "Leaderboard", sf::Vector2f(960.f, 100.f), 100, font);
	initText(&back, "Back", sf::Vector2f(960.f, 980.f), 60, font);
	for (int i = 0; i < 5; i++) {
		std::stringstream ss;
		ss << i + 1 << ".  " << d[i].name << "      >      " << d[i].score << "   points";
		std::string str = ss.str();
		float posY = 300.f + i * 125.f;
		initText(&scoreData[i], str, sf::Vector2f(960.f, posY), 45, font);
	}
}

ScoreState::~ScoreState()
{
}

void ScoreState::ReadFromFile(Data* d)
{
	char c;
	std::string str = "";
	std::ifstream file;
	int count = 0;
	file.open("score.txt");

	while (file.eof() == 0) {
		file.get(c);
		if (c == ' ') {
			strcpy_s(d[count].name, str.c_str());
			str = "";
		}
		else {
			if (c == '\n' || file.eof() != 0) {
				d[count].score = std::stoi(str);
				str = "";
				count++;
			}
			else {
				str += c;
			}
		}
	}
	file.close();
}

bool ScoreState::isHover(sf::Text* text, sf::Vector2i mousePos)
{
	if (mousePos.x >= text->getGlobalBounds().left && mousePos.x <= text->getLocalBounds().width + text->getGlobalBounds().left &&
		mousePos.y >= text->getGlobalBounds().top && mousePos.y <= text->getGlobalBounds().top + text->getLocalBounds().height) {
		text->setFillColor(sf::Color::Red);
		return true;
	}
	else {
		text->setFillColor(sf::Color::White);
		return false;
	}
}

void ScoreState::initText(sf::Text* text, std::string words, sf::Vector2f pos, int size, sf::Font& font)
{
	text->setFont(font);
	text->setCharacterSize(size);
	text->setString(words);
	text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
	text->setPosition(pos);
}

void ScoreState::Update(float deltaTime)
{
	clickDelay += deltaTime;

	sf::Event sfEvent;
	while (this->window->pollEvent(sfEvent)) {
		if (sfEvent.type == sf::Event::Closed)
			this->window->close();
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && clickDelay > 0.2f) {
		clickSound.play();
		SetIsEnd(true);
		clickDelay = 0.f;
	}

	if (isHover(&back, mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickDelay > 0.2f) {
			clickSound.play();
			SetIsEnd(true);
			clickDelay = 0.f;
		}
	}
}

void ScoreState::Render(sf::RenderTarget* target)
{
	target->setView(*view);
	target->draw(bg);
	target->draw(leaderboard);
	target->draw(back);
	for (int i = 0; i < 5; i++) {
		target->draw(scoreData[i]);
	}
}
