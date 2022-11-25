#ifndef MAPBOUND_H
#define MAPBOUND_H

#include "ResourceManager.h"
#include "Entity.h"

class MapBound : public Entity
{
private:
	sf::Texture texture;
	sf::Sprite body;

public:

private:

public:
	MapBound(int type, ResourceManager* resourceManager, sf::Vector2f spawnPos);
	~MapBound();

	void calculateCornersPos();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
};

#endif MAPBOUND_H
