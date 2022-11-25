#include "Item.h"

Item::Item(int type, ResourceManager* resourceManager, sf::Vector2f spawnPos) : Entity()
{
	this->type = type;

	this->font = resourceManager->getFont("Roboto");

	this->interactText.setFillColor(sf::Color::White);
	this->interactText.setFont(font);
	this->interactText.setCharacterSize(20);

	switch (type) {
	case 1: //Health
		body.setTexture(resourceManager->getTexture("Firstaid"));
		body.setScale(0.4f, 0.4f);
		itemName = "First Aid";
		break;
	case 2: //Ammo
		body.setTexture(resourceManager->getTexture("Ammo"));
		body.setScale(0.5f, 0.5f);
		itemName = "Ammo Box";
		break;
	case 3: //Nuke
		body.setTexture(resourceManager->getTexture("Nuke"));
		body.setScale(0.5f, 0.5f);
		itemName = "Nuke";
		break;
	case 4:
		body.setTexture(resourceManager->getTexture("Vaccine"));
		body.setScale(0.4f, 0.4f);
		itemName = "Vaccine";
		break;
	case 5:
		body.setTexture(resourceManager->getTexture("AKItem"));
		body.setScale(0.7f, 0.7f);
		itemName = "AK47";
		break;
	case 6:
		body.setTexture(resourceManager->getTexture("SGItem"));
		body.setScale(0.7f, 0.7f);
		itemName = "Shotgun";
		break;
	}
	this->body.setPosition(spawnPos);
	this->interactText.setPosition(body.getGlobalBounds().left, body.getGlobalBounds().top - 50);

	this->lifeTime = 10.f;
	this->isDead = false;
	this->totalTime = 0;
}

Item::~Item()
{
}

bool Item::CheckIsDead()
{
	return this->isDead;
}

void Item::Update(float deltaTime)
{
	this->totalTime += deltaTime;
	if (this->totalTime <= lifeTime) {
		if (this->totalTime >= lifeTime - 0.25) {
			body.setColor(sf::Color::White);
		}
		else if (this->totalTime >= lifeTime - 0.5) {
			body.setColor(sf::Color::Transparent);	
		}
		else if (this->totalTime >= lifeTime - 0.75) {
			body.setColor(sf::Color::White);
		}
		else if (this->totalTime >= lifeTime - 1) {
			body.setColor(sf::Color::Transparent);
		}
		else if (this->totalTime >= lifeTime - 1.25) {
			body.setColor(sf::Color::White);
		}
		else if (this->totalTime >= lifeTime - 1.5) {
			body.setColor(sf::Color::Transparent);
		}
	}
	else 
	{
		this->isDead = true;
	}

	this->calculateCornersPos();
}

void Item::ShowInteractText()
{
	std::stringstream ss;
	ss << "Press [F] to pick up " << itemName;
	std::string str = ss.str();
	this->interactText.setString(str);
}

void Item::HideInteractText()
{
	std::stringstream ss;
	ss << "";
	std::string str = ss.str();
	this->interactText.setString(str);
}

void Item::calculateCornersPos()
{
	sf::FloatRect spriteBounds = this->body.getLocalBounds();

	topLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top));
	topRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top));
	bottomRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top + spriteBounds.height));
	bottomLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top + spriteBounds.height));
}

void Item::Render(sf::RenderTarget* target)
{
	target->draw(body);
	target->draw(interactText);
	//this->showCollisionArea(target); //need to comment later
}
