#include "Enemy.h"

Enemy::Enemy(float HP, float speed, float dmg, sf::Vector2f spawnPos, int type, ResourceManager* resourceManager) : Entity(), Animation(resourceManager)
{
	this->resourceManager = resourceManager;
	this->deltaTime = 0.f;
	this->stuntDelay = 0.f;
	this->stuntElasped = 0.f;
	this->attackDelay = 0.f;
	this->isStunt = false;

	this->HP = HP;
	this->speed = speed;
	this->dmg = dmg;
	this->isDead = false;

	this->isAttack = false;

	this->texture = resourceManager->getTexture("Enemy");

	this->body.setTexture(texture);
	this->body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
	switch (type) {
	case 1:
		this->body.setScale(0.7f, 0.7f);
		this->score = 1;
		break;
	case 2:
		this->body.setColor(sf::Color::Red);
		this->body.setScale(0.65f, 0.65f);
		this->score = 2;
		break;
	case 3:
		this->body.setColor(sf::Color::Magenta);
		this->body.setScale(1.f, 1.f);
		this->score = 5;
		break;
	}
	this->body.setPosition(sf::Vector2f(spawnPos));

	this->animTime = 0.f;
	this->frame = 0;
	this->attackFrame = 0;
}

Enemy::~Enemy()
{
	//delete this->resourceManager;
	std::cout << "Enemy destroyed" << std::endl;
}

void Enemy::loseHP(float playerDmg)
{
	this->HP -= playerDmg;
}

bool Enemy::CheckIsDead()
{
	return this->isDead;
}

void Enemy::StartAttackDelay(float deltaTime)
{
	this->isAttack = true;
	attackDelay += deltaTime;
}

void Enemy::Stunt(float time)
{
	this->stuntDelay = time;
	this->isStunt = true;
}

void Enemy::RotateToTargetandMove(sf::Vector2f targetPos)
{
	if (isStunt == false) {
		sf::Vector2f enemyPos = body.getPosition();

		float toX = targetPos.x - enemyPos.x;
		float toY = targetPos.y - enemyPos.y;
		float mag = sqrt((toX * toX) + (toY * toY));
		float dx = toX / mag;
		float dy = toY / mag;

		float rotation = (atan2(toY, toX)) * static_cast<__int64>(180) / PI; //Calculation don't ask how it just works

		body.setRotation(rotation);
		body.move(dx * speed * this->deltaTime, dy * speed * this->deltaTime);
	}
}

void Enemy::PlayHurtSound()
{
	int random = rand() % 2 + 1;
	if (random == 1) {
		HurtSound.setBuffer(resourceManager->getSoundBuffer("EnemyHurtSound1"));
	}
	else {
		HurtSound.setBuffer(resourceManager->getSoundBuffer("EnemyHurtSound2"));
	}
	HurtSound.play();
}

void Enemy::calculateCornersPos()
{
	sf::FloatRect spriteBounds = this->body.getLocalBounds();

	topLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + 60, spriteBounds.top + 67));
	topRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width - 140, spriteBounds.top + 67));
	bottomRightCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + spriteBounds.width - 140, spriteBounds.top + spriteBounds.height - 50));
	bottomLeftCorner = this->body.getTransform().transformPoint(sf::Vector2f(spriteBounds.left + 60, spriteBounds.top + spriteBounds.height - 50));
}

void Enemy::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	if (this->HP <= 0) {
		this->isDead = true;
	}

	stuntElasped += deltaTime;
	if (stuntElasped >= stuntDelay) {
		stuntElasped = 0.f;
		isStunt = false;
	}

	//AnimationUpdate
	if (isStunt == false) {
		this->animTime += deltaTime;
		if (isAttack) {
			if (animTime >= 0.05f) {
				attackFrame++;
				if (attackFrame > 8) {
					this->isAttack = false;
					attackFrame = 0;
				}
				this->texture = GetAnimFrame("EnemyAttack", attackFrame);
				this->body.setTexture(texture);
				animTime -= 0.05f;
			}
		}
		else {
			if (animTime >= 0.25f) {
				frame++;
				if (frame > 16) {
					frame = 0;
				}
				this->texture = GetAnimFrame("EnemyWalk", frame);
				this->body.setTexture(texture);
				animTime -= 0.25f;
			}
		}
	}

	this->calculateCornersPos(); //need to comment later
	//this->setCollisionArea(); //need to comment later
}

void Enemy::Render(sf::RenderTarget* target)
{
	target->draw(body);
	//this->showCollisionArea(target); //need to comment later
}
