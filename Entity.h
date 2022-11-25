#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>

#define PI 3.141593

class Entity
{
protected:
	sf::Vector2f topLeftCorner;
	sf::Vector2f topRightCorner;
	sf::Vector2f bottomRightCorner;
	sf::Vector2f bottomLeftCorner;

	sf::Sprite body;

private: //Variables
	sf::VertexArray* collisionArea;

public: //Variables

private: //Functions

public: //Functions
	Entity();
	virtual ~Entity();

	sf::Sprite& getObjShape() { return body; }
	sf::VertexArray* getCollisionArea() { return collisionArea; }
	void setCollisionArea();
	void showCollisionArea(sf::RenderTarget* target);

	virtual void calculateCornersPos();
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
};

#endif ENTITY_H

