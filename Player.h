#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Animation.h"
#include "Entity.h"
#include "PlayerAttack.h"
#include "Weapon.h"

class Player : public Entity, Animation
{
private: //Variables
	float HP, speed, maxHp, rotationAngle;
	float deltaTime, swapDelay, itemStateDelay, HPdepletedTime, HPdepletedDelay;
	int animFrame;
	int currentWeapon;
	int currentItem;
	int totalAmmo[3];
	bool isImmortal, isNukeActivated;

	sf::Texture texture;
	sf::Texture bulletTexture;
	std::vector<PlayerAttack*> bullets;
	sf::Vector2f BSP;
	sf::CircleShape bulletSpawnPos;

	sf::Sound useItemSound;
	sf::Sound yesScience;
	sf::Sound swapSound;
	sf::Sound hurtSound;

	Weapon* weaponSlots[2];
	int itemSlots[2] = { 0, 0 };
	ResourceManager* resourceManager;

public: //Variables

private: //Functions
	void ReloadAnim();
	void ShootAnim();

public: //Funtions
	Player(float HP, float speed, ResourceManager* resourceManager);
	virtual ~Player();

	void GetHPptr(float *HP);
	void loseHP(int amount, float time);
	bool GetIsImmortal() { return isImmortal; }
	bool GetNukeState() { return isNukeActivated; }
	void SetNukeState(bool state) { isNukeActivated = state; }
	void ResetHPDepletedTime() { HPdepletedTime = 0.f; }
	sf::Vector2f GetPos() { return body.getPosition(); }

	//Input 
	void Move(float x, float y);
	void Shoot(sf::Vector2f mouseCoord);
	void RotateToMouse(sf::Vector2f targetPos);
	void SwapCurrentWeapon();
	void SwapDropWeapon(int type);
	void SetNewItem(int type);
	void SwapCurrentItem();
	bool UseItem();

	Weapon& GetPlayerWeapon() { return *weaponSlots[currentWeapon]; }
	std::string GetOtherWeaponType();
	int GetItemType() { return itemSlots[currentItem]; }
	int GetAnotherItemType();
	std::vector<PlayerAttack*>& GetBulletObj();
	
	void calculateCornersPos();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
};

#endif PLAYER_H
