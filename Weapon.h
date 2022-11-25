#ifndef WEAPON_H
#define WEAPON_H

#include "PlayerAttack.h"
#include "ResourceManager.h"
#include <string>
#include <vector>

class Weapon
{
private: //Variables
	std::string type;
	int maxAmmo, ammoPerMag, ammoInMag;
	float lifeTime;
	int* remainingAmmo;
	float delay, reloadTimePass, shootTimePass, fireRate, dmg, bulletSpeed, reloadTime;
	bool isReload, isShoot, canPlayReload;
	sf::Texture bulletTexture;
	sf::Vector2f spawnPos;

	ResourceManager* resourceManager;
	sf::Sound empty;
	sf::Sound shootSound;
	sf::Sound shootSound2;
	sf::Sound reloadSound;

public: //Variables

private: //Functions

public: //Functions
	Weapon(std::string type, int* initAmmo, ResourceManager* resourceManager);
	virtual ~Weapon();

	bool GetShootInfo(float* dmg, float* lifeTime, float* bulletSpeed, sf::Vector2f* spawnPos, sf::Texture& bulletTexture);
	void Reload();

	std::string GetWeaponType() { return this->type; }
	void GetWeaponInfo(int* ammoInMag, int* ammoRemained, std::string* weaponType);
	bool GetReloadState() { return isReload; }
	bool GetShootState() { return isShoot; }
	float GetReloadTimePass() { return reloadTimePass; }
	float GetShootTimePass() { return shootTimePass; }

	void PlayReloadSound();
	void PlayShootSound(int soundNum);

	std::vector<PlayerAttack>& GetBulletObj();
	void Update(sf::Vector2f spawnPos, float deltaTime);
	void Render(sf::RenderTarget* target);
};

#endif WEAPON_H

