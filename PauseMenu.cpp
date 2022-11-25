#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr, bool* isEndtoMain) : State(window, resourceManager, statesPtr)
{
	this->resourceManager = resourceManager;
	this->clickDelay = 0.f;
	this->isEndtoMain = isEndtoMain;
	this->view->setCenter(sf::Vector2f(960.f, 540.f));

	this->font = resourceManager->getFont("ZombieQueen");
	this->clickSound.setBuffer(this->resourceManager->getSoundBuffer("ClickButton"));
	this->bg.setTexture(this->resourceManager->getTexture("MainmenuBG"));

	initText(&Title, "Pause", sf::Vector2f(960.f, 100.f), 100, font);
	initText(&resumeButton, "Resume", sf::Vector2f(960.f, 500.f), 60, font);
	initText(&quitButton, "Quit", sf::Vector2f(960.f, 750.f), 60, font);
}

PauseMenu::~PauseMenu()
{

}

bool PauseMenu::isHover(sf::Text* text, sf::Vector2i mousePos)
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

void PauseMenu::initText(sf::Text* text, std::string words, sf::Vector2f pos, int size, sf::Font& font)
{
	text->setFont(font);
	text->setCharacterSize(size);
	text->setString(words);
	text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
	text->setPosition(pos);
}

void PauseMenu::Update(float deltaTime)
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
	}

	if (isHover(&resumeButton, mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickDelay > 0.2f) {
			clickSound.play();
			SetIsEnd(true);
			clickDelay = 0.f;
		}
	}

	if (isHover(&quitButton, mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickDelay > 0.2f) {
			clickSound.play();
			*isEndtoMain = true;
			SetIsEnd(true);
			clickDelay = 0.f;
		}
	}
}

void PauseMenu::Render(sf::RenderTarget* target)
{
	target->setView(*view);
	target->draw(bg);
	target->draw(Title);
	target->draw(resumeButton);
	target->draw(quitButton);
}