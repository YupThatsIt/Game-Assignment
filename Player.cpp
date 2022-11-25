//Player.cpp needs a new system to store item data
//It also desperately needs new way to shoot

#include "Player.h"

Player::Player(float maxHP, float speed, ResourceManager* resourceManager) : Entity(), Animation(resourceManager)
{
	this->resourceManager = resourceManager;
	this->HP = maxHP;
	this->maxHp = maxHP;
	this->speed = speed;
	this->deltaTime = 0;
  	this->texture = this->resourceManager->getTexture("PlayerAK");

	this->isImmortal = false;
	this->isNukeActivated = false;
	this->currentWeapon = 1;
	this->currentItem = 0;

	this->body.setTexture(this->texture);
	this->body.setScale(0.8f, 0.8f);
	this->body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
	this->body.setPosition(sf::Vector2f(960, 540));

	this->bulletSpawnPos.setFillColor(sf::Color::Red);
	this->bulletSpawnPos.setOrigin(bulletSpawnPos.getLocalBounds().width / 2, bulletSpawnPos.getLocalBounds().height / 2);
	this->bulletSpawnPos.setRadius(1.f);
	this->bulletSpawnPos.setPosition(body.getPosition());

	this->swapDelay = 0;
	this->itemStateDelay = 0;
	this->HPdepletedTime = 0;
	this->HPdepletedDelay = 0;

	this->totalAmmo[0] = -1;
	this->totalAmmo[1] = 90;
	this->totalAmmo[2] = 24;

	weaponSlots[0] = new Weapon("HG", &this->totalAmmo[0], resourceManager);
    weaponSlots[1] = new Weapon("AK", &this->totalAmmo[1], resourceManager);
	//weaponSlots[1] = new Weapon("SG", &this->totalAmmo[2], resourceManager);

	itemSlots[0] = 4;

	this->swapSound.setBuffer(this->resourceManager->getSoundBuffer("PickUpSound"));
	this->hurtSound.setBuffer(this->resourceManager->getSoundBuffer("PlayerHurt"));
	this->yesScience.setBuffer(this->resourceManager->getSoundBuffer("YesScience"));
	this->yesScience.setVolume(60);
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

void Player::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	swapDelay += this->deltaTime;

	this->bulletSpawnPos.setPosition(BSP);
	weaponSlots[currentWeapon]->Update(bulletSpawnPos.getPosition(), deltaTime);

	if (HPdepletedDelay > 0) {
		this->HPdepletedTime += this->deltaTime;
		if (this->HPdepletedTime < this->HPdepletedDelay) {
			this->body.setColor(sf::Color::Red);
		}
		else {
			this->body.setColor(sf::Color::White);
			this->HPdepletedDelay = 0.f;
			this->HPdepletedTime = 0.f;
		}
	}

	//Animation Update
	if (weaponSlots[currentWeapon]->GetReloadState()) {
		if (weaponSlots[currentWeapon]->GetWeaponType() == "HG") {
			if (weaponSlots[currentWeapon]->GetReloadTimePass() - (animFrame * 0.05) >= 0.05) {
				animFrame++;
			}
			this->texture = GetAnimFrame("PlayerHGReload", animFrame);
			this->body.setTexture(texture);
		}
		else if (weaponSlots[currentWeapon]->GetWeaponType() == "AK") {
			if (weaponSlots[currentWeapon]->GetReloadTimePass() - (animFrame * 0.05) >= 0.05) {
				animFrame++;
			}
			this->texture = GetAnimFrame("PlayerAKReload", animFrame);
			this->body.setTexture(texture);
		}
		else if (weaponSlots[currentWeapon]->GetWeaponType() == "SG") {
			if (weaponSlots[currentWeapon]->GetReloadTimePass() - (animFrame * 0.05) >= 0.05) {
				animFrame++;
			}
			this->texture = GetAnimFrame("PlayerSGReload", animFrame);
			this->body.setTexture(texture);
		}
	}
	else if (weaponSlots[currentWeapon]->GetShootState()) {
		if (weaponSlots[currentWeapon]->GetWeaponType() == "HG") {
			if (weaponSlots[currentWeapon]->GetShootTimePass() - (animFrame * 0.033) >= 0.033) {
				animFrame++;
			}
			this->texture = GetAnimFrame("PlayerHGShoot", animFrame);
			this->body.setTexture(texture);
		}
		else if (weaponSlots[currentWeapon]->GetWeaponType() == "AK") {
			if (weaponSlots[currentWeapon]->GetShootTimePass() - (animFrame * 0.033) >= 0.033) {
				animFrame++;
			}
			this->texture = GetAnimFrame("PlayerAKShoot", animFrame);
			this->body.setTexture(texture);
		}
		else if (weaponSlots[currentWeapon]->GetWeaponType() == "SG") {
			if (weaponSlots[currentWeapon]->GetShootTimePass() - (animFrame * 0.033) >= 0.033) {
				animFrame++;
			}
			this->texture = GetAnimFrame("PlayerSGShoot", animFrame);
			this->body.setTexture(texture);
		}
	}
	else {
		animFrame = 0;
		if (weaponSlots[currentWeapon]->GetWeaponType() == "HG") {
			this->texture = this->resourceManager->getTexture("PlayerHG");
			this->body.setTexture(texture);
		}
		else if (weaponSlots[currentWeapon]->GetWeaponType() == "AK") {
			this->texture = this->resourceManager->getTexture("PlayerAK");
			this->body.setTexture(texture);
		}
		else if (weaponSlots[currentWeapon]->GetWeaponType() == "SG") {
			this->texture = this->resourceManager->getTexture("PlayerSG");
			this->body.setTexture(texture);
		}
	}

	//bullet update
	for (size_t i = 0; i < bullets.size(); i++) {
		bullets[i]->Update(deltaTime);
		if (bullets[i]->CheckIfDead()) {
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}

	//Item state update
	if (isImmortal == true) {
		body.setColor(sf::Color::Blue);
		itemStateDelay += deltaTime;
		if (itemStateDelay >= 5.f) {
			isImmortal = false;
			body.setColor(sf::Color::White);
			itemStateDelay = 0;
		}
	}

	this->calculateCornersPos();
	//this->setCollisionArea(); //need to comment later
}

void Player::GetHPptr(float *HP)
{
	*HP = this->HP;
}

void Player::loseHP(int amount, float time)
{
	this->hurtSound.play();
	this->HP -= amount;
	this->HPdepletedDelay = time;
}

void Player::Shoot(sf::Vector2f mouseCoord)
{
	float dmg, lifeTime, speed;
	sf::Vector2f spawnPos;
	if (weaponSlots[currentWeapon]->GetShootInfo(&dmg, &lifeTime, &speed, &spawnPos, bulletTexture)) {
		if (weaponSlots[currentWeapon]->GetWeaponType() == "SG") {
			int diff;
			std::cout << "Angle : " << this->rotationAngle << std::endl;
			if ((this->rotationAngle >= 0 && this->rotationAngle <= 90) || (this->rotationAngle >= -180 && this->rotationAngle <= -90)) {
				diff = -1;
			}
			else {
				diff = 1;
			}
			bullets.push_back(new PlayerAttack(dmg, lifeTime, speed, spawnPos, mouseCoord, bulletTexture));
			bullets.push_back(new PlayerAttack(dmg, lifeTime, speed, spawnPos, sf::Vector2f(mouseCoord.x + diff * 40, mouseCoord.y + 40), bulletTexture));
			bullets.push_back(new PlayerAttack(dmg, lifeTime, speed, spawnPos, sf::Vector2f(mouseCoord.x - diff * 40, mouseCoord.y - 40), bulletTexture));
			bullets.push_back(new PlayerAttack(dmg, lifeTime, speed, spawnPos, sf::Vector2f(mouseCoord.x + diff * 80, mouseCoord.y + 80), bulletTexture));
			bullets.push_back(new PlayerAttack(dmg, lifeTime, speed, spawnPos, sf::Vector2f(mouseCoord.x - diff * 80, mouseCoord.y - 80), bulletTexture));
		}
		else {
			bullets.push_back(new PlayerAttack(dmg, lifeTime, speed, spawnPos, mouseCoord, bulletTexture));
		}
	}
}

void Player::Move(float x, float y)
{
	this->body.move(x * speed * deltaTime, y * speed * deltaTime);
}

std::string Player::GetOtherWeaponType()
{
	if (currentWeapon == 0) return weaponSlots[1]->GetWeaponType();
	else return weaponSlots[0]->GetWeaponType();
}

int Player::GetAnotherItemType()
{
	if (currentItem == 1) return itemSlots[0];
	else return itemSlots[1];
}

std::vector<PlayerAttack*>& Player::GetBulletObj(){
	return bullets;
}

void Player::SetNewItem(int type)
{
	if (currentItem == 0) {
		if (itemSlots[0] == 0) {
			itemSlots[0] = type;
		}
		else if (itemSlots[1] == 0) {
			itemSlots[1] = type;
		}
		else {
			itemSlots[currentItem] = 0;
			itemSlots[currentItem] = type;
		}
	}
	else if (currentItem == 1) {
		if (itemSlots[1] == 0) {
			itemSlots[1] = type;
		}
		else if (itemSlots[0] == 0) {
			itemSlots[0] = type;
		}
		else {
			itemSlots[currentItem] = 0;
			itemSlots[currentItem] = type;
		}
	}
	else {
		itemSlots[currentItem] = 0;
		itemSlots[currentItem] = type;
	}
}

bool Player::UseItem() {
	switch (itemSlots[currentItem]) {
	case 1 : //Heal -> Heal +50% health
		if (HP != maxHp) {
			useItemSound.setBuffer(resourceManager->getSoundBuffer("FirstaidSound"));
			useItemSound.play();
			HP += maxHp * 50 / 100;
			if (HP > maxHp) {
				HP = maxHp;
			}
			itemSlots[currentItem] = 0;
			return true;
		}
		break;
	case 2 : //Ammo -> add two more magazines to main weaponSlot
		useItemSound.setBuffer(resourceManager->getSoundBuffer("AmmoSound"));
		useItemSound.play();
		if (weaponSlots[1]->GetWeaponType() == "AK") {
			totalAmmo[1] += 90;
		}
		else {
			totalAmmo[2] += 24;
		}
		itemSlots[currentItem] = 0;
		return true;
		break;
	case 3 : //Nuke -> destroy every enemies on the field
		useItemSound.setBuffer(resourceManager->getSoundBuffer("NukeSound"));
		useItemSound.play();
		this->isNukeActivated = true;
		itemSlots[currentItem] = 0;
		return true;
		break;
	case 4 : //Vaccine -> Be immortal for 10s
		useItemSound.setBuffer(resourceManager->getSoundBuffer("VaccineSound"));
		useItemSound.play();
		yesScience.play();
		this->isImmortal = true;
		itemSlots[currentItem] = 0;
		return true;
		break;
	}
	return false;
}

void Player::SwapCurrentItem()
{
	if (swapDelay >= 0.2f) {
		swapSound.play();
		if (currentItem == 1) {
			currentItem = 0;
		}
		else {
			currentItem = 1;
		}
		swapDelay = 0.f;
	}
}

void Player::calculateCornersPos()
{
	sf::FloatRect spriteBounds = this->body.getLocalBounds();

	topLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + 40, spriteBounds.top + 60));
	topRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width - 80, spriteBounds.top + 60));
	bottomRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width - 80, spriteBounds.top + spriteBounds.height - 20));
	bottomLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + 40, spriteBounds.top + spriteBounds.height - 20));
	BSP = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width - 80, spriteBounds.top + spriteBounds.height - 50));
}

void Player::RotateToMouse(sf::Vector2f targetPos)
{
	sf::Vector2f playerPos = body.getPosition();

	float toX = targetPos.x - playerPos.x;
	float toY = targetPos.y - playerPos.y;

	float rotation = (atan2(toY, toX)) * static_cast<__int64>(180) / PI; //Calculation don't ask how it just works

	//std::cout << rotation << std::endl;
	this->rotationAngle = rotation;
	body.setRotation(rotation);
	//bulletSpawnPos.setRotation(rotation);
}

void Player::SwapCurrentWeapon()
{
	if (swapDelay >= 0.2f) {
		swapSound.play();
		if (currentWeapon == 1) {
			this->texture = this->resourceManager->getTexture("PlayerHG");
			this->body.setTexture(texture); //Need to make actuall animation class
			currentWeapon = 0;
		}
		else {
			if (weaponSlots[1]->GetWeaponType() == "AK") {
				this->texture = this->resourceManager->getTexture("PlayerAK");
				this->body.setTexture(texture); //Need to make actuall animation class
			}
			else {
				this->texture = this->resourceManager->getTexture("PlayerSG");
				this->body.setTexture(texture); //Need to make actuall animation class
			}
			currentWeapon = 1;
		}
		swapDelay = 0.f;
	}
}

void Player::SwapDropWeapon(int type)
{
	//std::cout << "Type : " << type << std::endl;
	if (type == 5) { //AK
		if (weaponSlots[1]->GetWeaponType() == "AK") {
			totalAmmo[1] += 30;
		}
		else {
			weaponSlots[1] = nullptr;
			delete weaponSlots[1];
			weaponSlots[1] = new Weapon("AK", &this->totalAmmo[1], resourceManager);
			//Swap to ak
		}
	}
	else if (type == 6) { //SG
		if (weaponSlots[1]->GetWeaponType() == "SG") {
			totalAmmo[2] += 8;
		}
		else {
			weaponSlots[1] = nullptr;
			delete weaponSlots[1];
			weaponSlots[1] = new Weapon("SG", &this->totalAmmo[2], resourceManager);
			//Swap to sg
		}
	}
	//delete current weapon -> add new weapon
}

void Player::Render(sf::RenderTarget* target)
{
	for (size_t i = 0; i < bullets.size(); i++) {
		bullets[i]->Render(target);
	}
	target->draw(body);
	//target->draw(bulletSpawnPos);
	//this->showCollisionArea(target); //need to comment later
}