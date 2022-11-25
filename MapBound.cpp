#include "MapBound.h"

MapBound::MapBound(int type, ResourceManager* resourceManager, sf::Vector2f spawnPos)
{
	switch (type) {
	case 1 :
		this->body.setTexture(resourceManager->getTexture("MapBoundTop"));
		break;
	case 2 :
		this->body.setTexture(resourceManager->getTexture("MapBoundBottom"));
		break;
	case 3 :
		this->body.setTexture(resourceManager->getTexture("MapBoundLeft"));
		break;
	case 4 :
		this->body.setTexture(resourceManager->getTexture("MapBoundRight"));
		break;
	}

	this->body.setScale(2.f, 2.f);
	this->body.setPosition(spawnPos);
}

MapBound::~MapBound()
{
	std::cout << "Map Destroyed" << std::endl;
}

void MapBound::calculateCornersPos()
{
	sf::FloatRect spriteBounds = this->body.getLocalBounds();

	topLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top));
	topRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top));
	bottomRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top + spriteBounds.height));
	bottomLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top + spriteBounds.height));
}

void MapBound::Update(float deltaTime)
{
	this->calculateCornersPos();
}

void MapBound::Render(sf::RenderTarget* target)
{
	target->draw(body);
	//this->showCollisionArea(target); //need to comment later
}
