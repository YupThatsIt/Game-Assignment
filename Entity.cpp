#include "Entity.h"

Entity::Entity()
{
	collisionArea = new sf::VertexArray(sf::LineStrip, 5);
	this->calculateCornersPos();

	this->setCollisionArea();

	//this->body.setTexture(texture);
	//this->body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
}

Entity::~Entity()
{
	//std::cout << "Entity deleted" << std::endl;
	delete this->collisionArea;
}

void Entity::calculateCornersPos()
{
	sf::FloatRect spriteBounds = this->body.getLocalBounds();

	topLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top));
	topRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top));
	bottomRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width, spriteBounds.top + spriteBounds.height));
	bottomLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top + spriteBounds.height));
}

void Entity::showCollisionArea(sf::RenderTarget* target)
{
	target->draw(*collisionArea);
}

void Entity::setCollisionArea()
{
	(*collisionArea)[0].position = topLeftCorner;
	(*collisionArea)[1].position = topRightCorner;
	(*collisionArea)[2].position = bottomRightCorner;
	(*collisionArea)[3].position = bottomLeftCorner;
	(*collisionArea)[4].position = topLeftCorner;

	for (int i = 0; i < 5; i++)
	{
		(*collisionArea)[i].color = sf::Color::Red;
	}

}
