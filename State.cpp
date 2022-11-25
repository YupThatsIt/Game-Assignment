#include "State.h"

State::State(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr)
{
	this->view = new sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(1920.f, 1080.f));
	this->statesPtr = statesPtr;
	this->window = window;
	this->isEnd = false;
}

State::~State()
{
	//delete this->statesPtr;
	//delete this->window;
	//delete this->view;
	std::cout << "State Delete" << std::endl;
}

void State::EndState()
{

}

void State::Render(sf::RenderTarget* target)
{
}

void State::SetIsEnd(bool isend)
{
	this->isEnd = isend;
}

const bool &State::GetIsEnd() const
{
	return this->isEnd;
}
