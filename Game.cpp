#include "Game.h"

Game::Game()
{
	this->InitWindow();
	this->InitResourceManager();
	this->InitState();

	this->deltaClock = new sf::Clock;
	this->deltaTime = 0.f;
}

Game::~Game()
{
	delete this->window;

	while (!this->state.empty()) {
		delete this->state.top();
		this->state.pop();
	}
}

void Game::InitWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "ZOMBIE SHOOTER", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::InitResourceManager()
{
	this->resourceManager = new ResourceManager();
}

void Game::InitState()
{
	this->state.push(new MainMenu(this->window, this->resourceManager, &this->state));
}

void Game::Update()
{
	this->deltaTime = deltaClock->restart().asSeconds();

	//while (this->window->pollEvent(this->sfEvent)) {
	//	if (this->sfEvent.type == sf::Event::Closed)
	//		this->window->close();
	//}

	if (!this->state.empty()) {
		this->state.top()->Update(this->deltaTime);

		if (this->state.top()->GetIsEnd()) {
			delete this->state.top();
			this->state.pop();
		}
	}
	else {
		this->window->close();
	}
}

void Game::Render()
{
	this->window->clear(sf::Color::Black);
	//Draw stuff in game
	if (!this->state.empty()) {
		this->state.top()->Render(this->window);
	}

	this->window->display();
}


void Game::Run()
{
	while (this->window->isOpen()) {
		this->Update();
		this->Render();
	}
}
