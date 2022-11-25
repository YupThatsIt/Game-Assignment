#ifndef PLAYERATTACK_H
#define PLAYERATTACK_H

#include "Entity.h"

class PlayerAttack : public Entity
{
private: //Variables
	float dmg, speed, timePast, lifeTime;
	float dx, dy;
	sf::Sprite body;
	sf::Texture texture;
	bool isDead;

public: //Variables

private: //Functions
	void Move(float speed, float deltaTime);

public: //Funtions
	PlayerAttack(float dmg, float lifeTime, float speed, sf::Vector2f body, sf::Vector2f mouseCoord, sf::Texture& texture);
	virtual ~PlayerAttack();

	float GetAttackDmg();
	bool CheckIfDead();
	void KillPlayerAttack();

	void calculateCornersPos();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
};

#endif PLAYERATTACK_H
