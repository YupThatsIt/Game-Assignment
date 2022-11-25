#ifndef ITEM_H //The whole point of "Item" this is to have collsion and able to edit player's attributes
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Entity.h"
#include "ResourceManager.h"

class Item : public Entity
{
private:
	sf::Text interactText;
	sf::Font font;

	sf::Sprite body;
	float lifeTime;
	float totalTime;
	int type;
	bool isDead;
	std::string itemName;

public:

private:

public:
	Item(int type, ResourceManager* resourceManager, sf::Vector2f spawnPos);
	~Item();

	void ShowInteractText();
	void HideInteractText();
	bool CheckIsDead();
	void SetIsDeath(bool state) { isDead = state; }
	int GetItemType() { return type; }

	void calculateCornersPos();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
};

#endif ITEM_H
