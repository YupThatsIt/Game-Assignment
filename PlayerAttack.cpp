#include "PlayerAttack.h"

PlayerAttack::PlayerAttack(float dmg, float lifeTime, float speed, sf::Vector2f goPos, sf::Vector2f mouseCoord, sf::Texture& texture) : Entity()
{
	this->dmg = dmg;
	this->speed = speed;
	this->lifeTime = lifeTime;
	this->isDead = false;
	this->timePast = 0;

	sf::Vector2f spawnPos = goPos;

	this->body.setTexture(texture);
	this->body.setScale(0.1f, 0.1f);
	this->body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
	this->body.setPosition(spawnPos);

	float toX = mouseCoord.x - spawnPos.x;
	float toY = mouseCoord.y - spawnPos.y;
	float mag = sqrt((toX * toX) + (toY * toY));
	dx = toX / mag;
	dy = toY / mag;

	float rotation = (atan2(toY, toX)) * static_cast<__int64>(180) / PI; //Calculation don't ask how it just works

	body.setRotation(rotation);
}

PlayerAttack::~PlayerAttack()
{
	//std::cout << "Bullet destroyed" << std::endl;
}

float PlayerAttack::GetAttackDmg()
{
	return this->dmg;
}

bool PlayerAttack::CheckIfDead()
{
	return this->isDead;
}

void PlayerAttack::KillPlayerAttack()
{
	this->isDead = true;
}

void PlayerAttack::Move(float speed, float deltaTime)
{
	this->body.move(dx * speed * deltaTime, dy * speed * deltaTime);
}

void PlayerAttack::calculateCornersPos()
{
	sf::FloatRect spriteBounds = this->body.getLocalBounds();

	topLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top + 200));
	topRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width - 30, spriteBounds.top + 200));
	bottomRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width - 30, spriteBounds.top + spriteBounds.height - 200));
	bottomLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left, spriteBounds.top + spriteBounds.height - 200));
}

void PlayerAttack::Update(float deltaTime)
{
	this->timePast += deltaTime;
	if (timePast >= lifeTime) {
		this->isDead = true;
	}
	Move(this->speed, deltaTime);

	//this->calculateCornersPos(); //need to comment later
	//this->setCollisionArea(); //need to comment later
}

void PlayerAttack::Render(sf::RenderTarget* target)
{
	target->draw(body);
	//this->showCollisionArea(target); //need to comment later
}
