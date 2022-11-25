#ifndef ENEMY_H
#define ENEMY_H

#include <sstream>

#include "Entity.h"
#include "Animation.h"

class Enemy : public Entity, Animation
{
private: //Variables
	float HP, speed, dmg;
	int frame, score, attackFrame;
	float deltaTime, stuntDelay, stuntElasped, attackDelay;
	sf::Texture texture;
	float animTime;
	bool isDead, isStunt, isAttack;

	ResourceManager* resourceManager;
	sf::Sound HurtSound;

public: //Variables

private: //Functions

public: //Funtions
	Enemy(float HP, float speed, float dmg, sf::Vector2f spawnPos, int type, ResourceManager* resourceManager);
	virtual ~Enemy();

	void loseHP(float playerDmg);
	float GetDamage() { return dmg; }
	int GetScore() { return score; };
	bool CheckIsDead();

	void StartAttackDelay(float deltaTime); //{ attackDelay += deltaTime; }
	float GetAttackDelay() { return attackDelay; }
	void ResetAttackDelay() { attackDelay = 0.f; }
	void Stunt(float time);
	void RotateToTargetandMove(sf::Vector2f targetPos);

	void PlayHurtSound();

	void calculateCornersPos();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
};

#endif ENEMY_H

