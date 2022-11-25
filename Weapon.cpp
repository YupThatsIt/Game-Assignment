//Redesign weapon.cpp to optimized the new system
//Inputs it needs : a weapon type with now number of bullet data
//Seperated initial in mag ammo and total ammo
//When swaping weapon -> erase old weapon object while maintaining existing total ammo data
//Create new weapon object according to item you just pick up
//Creat new item object according to old weapon object data
#include "Weapon.h" 
#include <iostream>

Weapon::Weapon(std::string type, int* initAmmo, ResourceManager* resourceManager)
{
	this->isReload = false;
	this->isShoot = false;
	this->canPlayReload = true;
	this->type = type;
	this->delay = 0;
	this->remainingAmmo = initAmmo;
	this->resourceManager = resourceManager;

	if (this->type == "AK") {
		this->lifeTime = 1.5f;
		this->maxAmmo = 150;
		this->ammoPerMag = 30;
		this->ammoInMag = 30;
		this->fireRate = 8;
		this->dmg = 17;
		this->bulletSpeed = 2000;
		this->reloadTime = 1.f;
		this->bulletTexture = resourceManager->getTexture("Bullet");
	}
	else if (this->type == "HG") {
		this->lifeTime = 1.3f;
		this->maxAmmo = 999;
		this->ammoPerMag = 9;
		this->ammoInMag = 9;
		this->fireRate = 4;
		this->dmg = 10;
		this->bulletSpeed = 1600;
		this->reloadTime = 0.75f;
		this->bulletTexture = resourceManager->getTexture("Bullet");
	}
	else if (this->type == "SG") {
		this->lifeTime = 0.5f;
		this->maxAmmo = 40;
		this->ammoPerMag = 8;
		this->ammoInMag = 8;
		this->fireRate = 1;
		this->dmg = 13;
		this->bulletSpeed = 1600;
		this->reloadTime = 1.f;
		this->bulletTexture = resourceManager->getTexture("Bullet");
	}
}

Weapon::~Weapon()
{
	delete this->remainingAmmo;
}

bool Weapon::GetShootInfo(float* dmg, float* lifeTime, float* bulletSpeed, sf::Vector2f* spawnPos, sf::Texture& bulletTexture)
{
	if (isReload == false) {
			if (delay > 1.f / fireRate && ammoInMag != 0) {
				if (ammoInMag % 2 == 0) {
					PlayShootSound(1);
				}
				else {
					PlayShootSound(2);
				}
				ammoInMag -= 1;
				this->shootTimePass = 0;
				this->isShoot = true;
				*dmg = this->dmg;
				*lifeTime = this->lifeTime;
				*bulletSpeed = this->bulletSpeed;
				*spawnPos = this->spawnPos;
				bulletTexture = this->bulletTexture;
				delay = 0.f;
				return true;
				//return PlayerAttack(this->dmg, 2.f, this->bulletSpeed, this->spawnPos, this->bulletTexture);
			}
			else if (ammoInMag == 0) {
				if (delay >= 0.7f) {
					empty.setBuffer(this->resourceManager->getSoundBuffer("EmptyGun"));
					empty.setVolume(50);
					empty.play();
					delay -= 0.7f;
				}
			}
		return false;
	}
}

void Weapon::Reload()
{
	if (isReload == false) {
		this->reloadTimePass = 0;
		std::cout << isReload << std::endl;
		isReload = true;
	}
}
void Weapon::GetWeaponInfo(int* ammoInMag, int* ammoRemained, std::string* weaponType)
{
	*ammoInMag = this->ammoInMag;
	*ammoRemained = *this->remainingAmmo;
	*weaponType = this->type;
}

void Weapon::Update(sf::Vector2f spawnPos, float deltaTime)
{
	this->spawnPos = spawnPos;
	this->delay += deltaTime;

	if (isReload) {
		if (*remainingAmmo == 0 || ammoInMag == ammoPerMag) {
			isReload = false;
		}
		else {
			if (this->canPlayReload) {
				PlayReloadSound();
				this->canPlayReload = false;
			}
			reloadTimePass += deltaTime;
			if (reloadTimePass >= reloadTime) {
				if (*remainingAmmo < 0) {
					ammoInMag = ammoPerMag;
				}
				else if (*remainingAmmo + ammoInMag > ammoPerMag) {
					*remainingAmmo -= (ammoPerMag - ammoInMag);
					ammoInMag = ammoPerMag;
				}
				else {
					ammoInMag += *remainingAmmo;
					*remainingAmmo = 0;
				}
				isReload = false;
				this->canPlayReload = true;
			}
		}
	}

	if (isShoot) {
		shootTimePass += deltaTime;
		if (shootTimePass >= 0.099f) {
			isShoot = false;
		}
	}
}

void Weapon::PlayReloadSound() {
	if (this->type == "AK") {
		reloadSound.setBuffer(this->resourceManager->getSoundBuffer("AKReloadSound"));
	}
	else if (this->type == "SG") {
		reloadSound.setBuffer(this->resourceManager->getSoundBuffer("SGReloadSound"));
	}
	else {
		reloadSound.setBuffer(this->resourceManager->getSoundBuffer("HGReloadSound"));
	}
	reloadSound.play();
}

void Weapon::PlayShootSound(int soundNum) {
	if (soundNum == 1) {
		if (this->type == "AK") {
			shootSound.setBuffer(this->resourceManager->getSoundBuffer("AKShootSound"));
		}
		else if (this->type == "SG") {
			shootSound.setBuffer(this->resourceManager->getSoundBuffer("SGShootSound"));
		}
		else {
			shootSound.setBuffer(this->resourceManager->getSoundBuffer("HGShootSound"));
		}
		shootSound.play();
	}
	else {
		if (this->type == "AK") {
			shootSound2.setBuffer(this->resourceManager->getSoundBuffer("AKShootSound"));
		}
		else if (this->type == "SG") {
			shootSound2.setBuffer(this->resourceManager->getSoundBuffer("SGShootSound"));
		}
		else {
			shootSound2.setBuffer(this->resourceManager->getSoundBuffer("HGShootSound"));
		}
		shootSound2.play();
	}
}

void Weapon::Render(sf::RenderTarget* target)
{

}
