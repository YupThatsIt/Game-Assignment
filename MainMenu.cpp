#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr) : State(window, resourceManager, statesPtr)
{
	this->resourceManager = resourceManager;
	this->clickDelay = 0.f;
	this->view->setCenter(sf::Vector2f(960.f, 540.f));
	this->clickSound.setBuffer(this->resourceManager->getSoundBuffer("ButtonClick"));
	this->resumeMusic = false;

	font = resourceManager->getFont("ZombieQueen");

	this->bg.setTexture(this->resourceManager->getTexture("MainmenuBG"));
	if (!this->mainMenuTheme.openFromFile("Resources/Music/MainMenuTheme.ogg")) { std::cout << "Can't load music" << std::endl; }
	mainMenuTheme.play();
	mainMenuTheme.setLoop(true);

	initText(&Title, "ZOMBIE SHOOTER", sf::Vector2f(960.f, 100.f), 100, font);
	initText(&playButton, "Play", sf::Vector2f(960.f, 450.f), 60, font);
	initText(&leaderBoardButton, "Leaderboard", sf::Vector2f(960.f, 625.f), 60, font);
	initText(&quitButton, "Quit", sf::Vector2f(960.f, 800.f), 60, font);
	initText(&name, "SAI PRAPAMONTON 65010385", sf::Vector2f(200.f, 1000.f), 40, font);
}

MainMenu::~MainMenu()
{
}

bool MainMenu::isHover(sf::Text* text,sf::Vector2i mousePos)
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

void MainMenu::initText(sf::Text* text, std::string words, sf::Vector2f pos, int size, sf::Font& font)
{
	text->setFont(font);
	text->setCharacterSize(size);
	text->setString(words);
	text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
	text->setPosition(pos);
}

void MainMenu::ToNextState(int stateNum) {
	switch (stateNum) {
	case 1: 
		this->statesPtr->push(new PlayState(this->window, this->resourceManager, this->statesPtr));
		resumeMusic = true;
		mainMenuTheme.stop();
		break;
	case 2: //For Leaderboard
		this->statesPtr->push(new ScoreState(this->window, this->resourceManager, this->statesPtr));
		break;
	}
}

void MainMenu::Update(float deltaTime)
{
	clickDelay += deltaTime;

	if (resumeMusic) {
		mainMenuTheme.play();
		resumeMusic = false;
	}

	sf::Event sfEvent;
	while (this->window->pollEvent(sfEvent)) {
		if (sfEvent.type == sf::Event::Closed)
			this->window->close();
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition();

	if (isHover(&playButton, mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickDelay > 0.2f) {
			clickSound.play();
			ToNextState(1);
			clickDelay = 0.f;
		}
	}

	if (isHover(&leaderBoardButton, mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickDelay > 0.2f) {
			clickSound.play();
			ToNextState(2);
			clickDelay = 0.f;
		}
	}

	if (isHover(&quitButton, mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickDelay > 0.2f) {
			clickSound.play();
			SetIsEnd(true);
			clickDelay = 0.f;
		}
	}
}

void MainMenu::Render(sf::RenderTarget* target)
{
	target->setView(*view);
	target->draw(bg);
	target->draw(name);
	target->draw(Title);
	target->draw(playButton);
	target->draw(leaderBoardButton);
	target->draw(quitButton);
}