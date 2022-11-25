#include "PlayState.h"

PlayState::PlayState(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr) : State(window, resourceManager, statesPtr)
{
	this->resourceManager = resourceManager;
	this->endGame = false;
	this->font = resourceManager->getFont("ZombieQueen");
	this->canShootTime = 0.0f;
	this->canShoot = true;

	//Init text
	this->playerNameText.setFillColor(sf::Color::White);
	this->playerNameText.setCharacterSize(50);
	this->playerNameText.setOrigin(0.f, playerNameText.getLocalBounds().height / 2);
	this->playerNameText.setFont(font);

	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setString("Game Over");
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFont(font);

	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setCharacterSize(50);
	this->scoreText.setFont(font);

	//Init crosshair
	this->crosshair.setTexture(this->resourceManager->getTexture("Crosshair"));
	this->crosshair.setOrigin(crosshair.getLocalBounds().width / 2, crosshair.getLocalBounds().height / 2);
	this->crosshair.setScale(0.1f, 0.1f);

	//Player config here
	this->player = new Player(100.f, 350.f, this->resourceManager);

	this->gui = new GUI(this->resourceManager);
	this->sat = new SAT();

	this->difficulty = 1.f;
	this->score = 0;

	this->difficultyDelay = 0.f;
	this->enemySpawnDelay = 0.f;
	this->itemSpawnDelay = 0.f;
	this->clickDelay = 0.f;
	this->displayUseItemDelay = 0.f;

	this->isEndtoMain = false;
	this->isUseItem = false;

	//Init ammo
	this->ammoInMag = 0;
	this->ammoRemained = 0;

	//Init player
	this->playerHP = 0;

	//Init map
	InitMap();

	//Init music
	this->isSadMusicOn = false;
	if (!this->sadMusic.openFromFile("Resources/Music/SadMusic.ogg")) { std::cout << "Can't open sadMusic" << std::endl; }
}

PlayState::~PlayState()
{
	delete this->player;
	delete this->gui;
	delete this->view;
	delete this->sat;
	while (enemiesVect.size() != 0) {
		delete enemiesVect[0];
		enemiesVect.erase(enemiesVect.begin());
	}
	while (itemVect.size() != 0) {
		delete itemVect[0];
		itemVect.erase(itemVect.begin());
	}
	for (size_t i = 0; i < 4; i++) {
		delete mapBounds[i];
	}
}

void PlayState::InitMap() {
	this->map.setTexture(resourceManager->getTexture("Map"));
	this->map.setOrigin(map.getLocalBounds().width / 2, map.getLocalBounds().height / 2);
	this->map.setScale(2.f, 2.f);
	this->map.setPosition(960.f, 540.f);

	mapBounds[0] = new MapBound(1, this->resourceManager, sf::Vector2f(this->map.getGlobalBounds().left + 400, this->map.getGlobalBounds().top)); //Top
	mapBounds[1] = new MapBound(2, this->resourceManager, sf::Vector2f(this->map.getGlobalBounds().left + 400, this->map.getGlobalBounds().top + 2 * this->map.getLocalBounds().height - 400)); //Bottom
	mapBounds[2] = new MapBound(3, this->resourceManager, sf::Vector2f(this->map.getGlobalBounds().left, this->map.getGlobalBounds().top + 60)); //Left
	mapBounds[3] = new MapBound(4, this->resourceManager, sf::Vector2f(this->map.getGlobalBounds().left + 2 * this->map.getLocalBounds().width - 388, this->map.getGlobalBounds().top + 60)); //Right

	mapBoundsBlack[0].setFillColor(sf::Color::Black);
	mapBoundsBlack[0].setSize(sf::Vector2f(5000.f, 800.f));
	mapBoundsBlack[0].setOrigin(sf::Vector2f(2500.f, 400.f));
	mapBoundsBlack[0].setPosition(sf::Vector2f(960.f, -1150.f));

	mapBoundsBlack[1].setFillColor(sf::Color::Black);
	mapBoundsBlack[1].setSize(sf::Vector2f(5000.f, 800.f));
	mapBoundsBlack[1].setOrigin(sf::Vector2f(2500.f, 400.f));
	mapBoundsBlack[1].setPosition(sf::Vector2f(960.f, 2200.f));

	mapBoundsBlack[2].setFillColor(sf::Color::Black);
	mapBoundsBlack[2].setSize(sf::Vector2f(800.f, 4000.f));
	mapBoundsBlack[2].setOrigin(sf::Vector2f(400.f, 2000.f));
	mapBoundsBlack[2].setPosition(sf::Vector2f(-1500.f, 540.f));

	mapBoundsBlack[3].setFillColor(sf::Color::Black);
	mapBoundsBlack[3].setSize(sf::Vector2f(800.f, 4000.f));
	mapBoundsBlack[3].setOrigin(sf::Vector2f(400.f, 2000.f));
	mapBoundsBlack[3].setPosition(sf::Vector2f(3500.f, 540.f));
}

void PlayState::ToNextState(int stateNum) {
	switch (stateNum) {
	case 1:
		window->setMouseCursorVisible(true);
		canShoot = false;
		this->statesPtr->push(new PauseMenu(this->window, this->resourceManager, this->statesPtr, &this->isEndtoMain));
		break;
	}

}

void PlayState::Update(float deltaTime)
{
	this->clickDelay += deltaTime;
	if (this->endGame == false) {
		this->window->setMouseCursorVisible(false);
	}

	if (canShoot == false) {
		canShootTime += deltaTime;
		if (canShootTime >= 0.2f) {
			canShoot = true;
			canShootTime = 0.0f;
		}
	}

	//End game
	player->GetHPptr(&playerHP);
	if (playerHP <= 0 || isEndtoMain == true) {
		std::stringstream ss;
		ss << "  Your Score Is : " << this->score << "\nGood Luck Next Time";
		std::string str = ss.str();
		this->scoreText.setString(str);
		this->endGame = true;

		if (isSadMusicOn == false) {
			this->sadMusic.play();
			isSadMusicOn = true;
		}

		this->gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
		this->scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
		this->gameOverText.setPosition((*window).mapPixelToCoords(sf::Vector2i(960, 100)));
		this->scoreText.setPosition((*window).mapPixelToCoords(sf::Vector2i(960, 250)));
		this->playerNameText.setPosition((*window).mapPixelToCoords(sf::Vector2i(200, 490)));
	}
	
	if (this->endGame == true) {
		sf::Event sfEvent;
		while (this->window->pollEvent(sfEvent)) {
			if (sfEvent.type == sf::Event::Closed)
				this->window->close();

			if (sfEvent.type == sf::Event::TextEntered)
			{
				if (sfEvent.text.unicode < 128) {
					if (sfEvent.text.unicode == 13) { //Enter Key
						if (this->playerNameStr.size() != 0) {
							SaveScore();
							this->sadMusic.stop();
							this->SetIsEnd(true);
						}
					}
					else if (sfEvent.text.unicode == 8) { //Backspace Key
						if (this->playerNameStr.size() > 0) {
							this->playerNameStr.resize(this->playerNameStr.size() - 1);
						}
					}
					else if (this->playerNameStr.size() < 25 && sfEvent.text.unicode != 32 && sfEvent.text.unicode != 27) {
						this->playerNameStr += sfEvent.text.unicode;
					}
				}
			}
		}

		//Set playerNameText
		std::stringstream ss;
		ss << "Enter Your Name : " << playerNameStr << "_";
		if (this->playerNameStr.size() != 0) {
			ss << "\n\n\"Enter\" to continue...";
		}
		std::string nameText = ss.str();
		this->playerNameText.setString(nameText);
	}
	else {
		sf::Event sfEvent;
		while (this->window->pollEvent(sfEvent)) {
			if (sfEvent.type == sf::Event::Closed)
				this->window->close();
		}

		//Player Input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->player->Move(-1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->player->Move(1, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->player->Move(0, -1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->player->Move(0, 1);
		}
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f mouseCoord = (*window).mapPixelToCoords(mousePos);
		this->crosshair.setPosition(mouseCoord);
		this->player->RotateToMouse(mouseCoord);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			this->player->GetPlayerWeapon().Reload();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			this->player->SwapCurrentWeapon();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			this->player->SwapCurrentItem();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (isUseItem == false) {
				this->ItemType = this->player->GetItemType();
				if (this->player->UseItem()) {
					isUseItem = true;
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (canShoot) {
				this->player->Shoot(mouseCoord); //This is a problem
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			if (clickDelay > 0.2f) {
				this->ToNextState(1);
				clickDelay = 0;
			}
		}

		this->player->Update(deltaTime);

		//Enemy Update
		this->difficultyDelay += deltaTime;
		if (this->difficultyDelay > 6.f) {
			this->difficulty += 0.33f;
			difficultyDelay -= 6.f;
		}
		this->SpawnEnemy(deltaTime);
		this->EnemyUpdate(deltaTime);


		//Collision
		this->Collsion(deltaTime);

		//Item Update
		this->SpawnItem(deltaTime);
		this->ItemUpdate(deltaTime);

		//MapBound Update
		for (size_t i = 0; i < 4; i++) {
			mapBounds[i]->Update(deltaTime);
		}

		//View
		view->setCenter(player->GetPos());

		//Display gui
		gui->UpdatePlayerProp(&playerHP, &playerPower, (*window).mapPixelToCoords(sf::Vector2i(10, 10)));
		player->GetPlayerWeapon().GetWeaponInfo(&ammoInMag, &ammoRemained, &weaponType);
		gui->UpdateAmmo(&ammoInMag, &ammoRemained, &weaponType, player->GetOtherWeaponType(), (*window).mapPixelToCoords(sf::Vector2i(1550, 10)));
		gui->UpdateScore(&score, (*window).mapPixelToCoords(sf::Vector2i(10, 300)));
		gui->UpdateItem(player->GetItemType(), player->GetAnotherItemType(), (*window).mapPixelToCoords(sf::Vector2i(1550, 300)));
		if (isUseItem == true) {
			gui->UseItemEffect(this->ItemType, 1, sf::Vector2f(player->GetPos().x - 70, player->GetPos().y - 150));
			displayUseItemDelay += deltaTime;
			if (displayUseItemDelay >= 2.5f) {
				isUseItem = false;
				displayUseItemDelay = 0.f;
				gui->UseItemEffect(this->ItemType, 0, sf::Vector2f(player->GetPos().x - 70, player->GetPos().y - 150));
				this->ItemType = 0;
			}
		}
	}
}

void PlayState::SpawnEnemy(float deltaTime)
{
	this->enemySpawnDelay += deltaTime;
	if (this->enemySpawnDelay >= (-log(difficulty) + 1.5) && enemiesVect.size() <= 20 + difficulty * 2) {
		int randX = 0;
		int randY = 0;
		int randDir = rand() % 4;
		switch (randDir)
		{
		case 0:
			randX = rand() % 2020 - 50;
			randY = rand() % 50 - 200;
			break;
		case 1:
			randX = rand() % 50 - 200;
			randY = rand() % 1280 - 50;
			break;
		case 2:
			randX = rand() % 2020 - 50;
			randY = rand() % 50 + 1180;
			break;
		case 3:
			randX = rand() % 50 + 2020;
			randY = rand() % 1280 - 50;
			break;
		}

		sf::Vector2f spawnPos = (*window).mapPixelToCoords(sf::Vector2i(randX, randY));

		int randomEnemyPerc = rand() % 100;

		if ((int)difficulty % 5 == 0) { //Rush Hour
			enemiesVect.push_back(new Enemy(5.f + difficulty * 2, 350.f + difficulty * 5, 3.f, sf::Vector2f(spawnPos), 2, resourceManager)); //Rush Hour
		}
		else {
			if (randomEnemyPerc <= 5 + (difficulty / 4)) { enemiesVect.push_back(new Enemy(75.f + 4 * difficulty, 50.f + difficulty * 7, 20.f, sf::Vector2f(spawnPos), 3, resourceManager)); }
			else if (randomEnemyPerc <= 15 + (difficulty / 3)) { enemiesVect.push_back(new Enemy(5.f + difficulty * 2, 350.f + difficulty * 7, 3.f, sf::Vector2f(spawnPos), 2, resourceManager)); }
			else { enemiesVect.push_back(new Enemy(20.f + difficulty * 2, 100.f + difficulty * 7, 5.f, sf::Vector2f(spawnPos), 1, resourceManager)); }
		}	
		this->enemySpawnDelay = 0;
	}
}

void PlayState::EnemyUpdate(float deltaTime)
{
	for (size_t i = 0; i < enemiesVect.size(); i++) {
		enemiesVect[i]->Update(deltaTime);
		enemiesVect[i]->RotateToTargetandMove(this->player->GetPos()); //move and rotate
		if (enemiesVect[i]->CheckIsDead()) {
			enemyDeadSound.setBuffer(resourceManager->getSoundBuffer("EnemyDeadSound"));
			enemyDeadSound.play();
			int sc = enemiesVect[i]->GetScore();
			this->score += sc;
			delete enemiesVect[i];
			enemiesVect.erase(enemiesVect.begin() + i);
		}
	}
}

void PlayState::SpawnItem(float deltaTime)
{
	this->itemSpawnDelay += deltaTime;
	if (this->itemSpawnDelay >= 5) {
		int randX = 0;
		int randY = 0;
		int randType = 0;
		randX = rand() % static_cast<int>(this->map.getLocalBounds().width - 400) + this->map.getGlobalBounds().left + 400;
		randY = rand() % static_cast<int>(this->map.getLocalBounds().height - 400) + this->map.getGlobalBounds().top + 400;
		randType = rand() % 6 + 1;

		sf::Vector2f spawnPos(randX, randY);
		itemVect.push_back(new Item(randType, this->resourceManager, spawnPos));

		itemSpawnDelay -= 5.f;
	}
}

int PlayState::Compare(const void* a, const void* b)
{
	const Data* ptrA = (Data*)a;
	const Data* ptrB = (Data*)b;
	if (ptrA->score > ptrB->score) return -1;
	if (ptrA->score < ptrB->score) return 1;
	return 0;
}

void PlayState::SaveScore()
{
	Data d[6];
	d[5].score = this->score;
	strcpy_s(d[5].name, this->playerNameStr.c_str());
	//Input from the program

	ReadFromFile(d);

	int elementSize = sizeof(d[0]);
	int arraySize = sizeof(d) / sizeof(d[0]);
	std::qsort(d, arraySize, elementSize, Compare);

	WriteOnToFile(d);
}

void PlayState::WriteOnToFile(Data* d)
{
	std::ofstream file;
	file.open("score.txt");
	for (int i = 0; i < 4; i++) {
		file << d[i].name << " " << d[i].score << "\n";
	}
	file << d[4].name << " " << d[4].score;
	file.close();
}

void PlayState::ReadFromFile(Data* d)
{
	char c;
	std::string str = "";
	std::ifstream file;
	int count = 0;
	file.open("score.txt");

	while (file.eof() == 0) {
		file.get(c);
		if (c == ' ') {
			strcpy_s(d[count].name, str.c_str());
			str = "";
		}
		else {
			if (c == '\n' || file.eof() != 0) {
				d[count].score = std::stoi(str);
				str = "";
				count++;
			}
			else {
				str += c;
			}
		}
	}
	file.close();
}

void PlayState::ItemUpdate(float deltaTime) {
	//Item on the ground
	for (size_t i = 0; i < itemVect.size(); i++) {
		itemVect[i]->Update(deltaTime);
		if (itemVect[i]->CheckIsDead()) {
			delete itemVect[i];
			itemVect.erase(itemVect.begin() + i);
		}
	}

	//Item on hand
	if (player->GetNukeState()) {
		this->enemySpawnDelay = 0.0f; //Stop spawning
		while (enemiesVect.size() != 0) {
			delete enemiesVect[0];
			enemiesVect.erase(enemiesVect.begin());
			this->score++;
		}
		player->SetNukeState(false);
	}
}


void PlayState::Collsion(float deltaTime)
{
	//Enemy check
	for (size_t i = 0; i < enemiesVect.size(); i++) {
		for (size_t j = 0; j < enemiesVect.size(); j++) {
			if (sat->collisionSAT(*enemiesVect[j], *enemiesVect[i])) {
				sf::Vector2f moveValue = sat->calculateMoveValue(*enemiesVect[j], *enemiesVect[i], *sat);
				enemiesVect[j]->getObjShape().move(moveValue.x * deltaTime * 10, moveValue.y * deltaTime * 10);
			}
		}
	}

	//Enemy-Attack check -> Enemy lose HP 
	for (size_t i = 0; i < enemiesVect.size(); i++) {
		for (size_t j = 0; j < player->GetBulletObj().size(); j++) {
			if (sat->collisionSAT(*enemiesVect[i], *player->GetBulletObj()[j])) {
				sf::Vector2f moveValue = sat->calculateMoveValue(*enemiesVect[i], *player, *sat);
				enemiesVect[i]->getObjShape().move(moveValue.x * deltaTime * 20, moveValue.y * deltaTime * 20);
				enemiesVect[i]->PlayHurtSound();
				enemiesVect[i]->loseHP(player->GetBulletObj()[j]->GetAttackDmg());
				if (enemiesVect[i]->GetScore() != 5) {
					enemiesVect[i]->Stunt(0.05f);
				}
				player->GetBulletObj()[j]->KillPlayerAttack(); //Problem
			}
		}
	}
	
	//Enemy-Player -> Player lose HP
	for (size_t i = 0; i < enemiesVect.size(); i++) {
		if (sat->collisionSAT(*enemiesVect[i], *player)) {
			sf::Vector2f moveValue = sat->calculateMoveValue(*enemiesVect[i], *player, *sat);
			enemiesVect[i]->getObjShape().move(moveValue.x * deltaTime * 20, moveValue.y * deltaTime * 20);
			if (player->GetIsImmortal() == false) {
				enemiesVect[i]->StartAttackDelay(deltaTime);
				if (enemiesVect[i]->GetAttackDelay() > 0.27f){
					player->loseHP(enemiesVect[i]->GetDamage(), 0.15f);
					enemiesVect[i]->ResetAttackDelay();
				}
				else {
					player->ResetHPDepletedTime();
				}
			}
		}
		else {
			//std::cout << "isThisWorking" << std::endl;
			//player->ResetHPDepletedTime();
			enemiesVect[i]->ResetAttackDelay();
		}
	}

	//Player-Item -> Player has a choice to pick up item
	for (size_t i = 0; i < itemVect.size(); i++) {
		if (sat->collisionSAT(*itemVect[i], *player)) {
			//PickUp item -> delete item -> add item to player
			itemVect[i]->ShowInteractText();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				pickUpSound.setBuffer(resourceManager->getSoundBuffer("PickUpSound"));
				pickUpSound.play();
				if (itemVect[i]->GetItemType() > 4) {
					player->SwapDropWeapon(itemVect[i]->GetItemType());
				}
				else {
					player->SetNewItem(itemVect[i]->GetItemType());
				}
				itemVect[i]->SetIsDeath(true);
			}
		}
		else {
			itemVect[i]->HideInteractText();
		}
	}

	//Player-MapBound
	float moveValue = 75.f;
	if (sat->collisionSAT(*mapBounds[0], *player)) {
		player->Move(0.f, moveValue * deltaTime);
	}
	if (sat->collisionSAT(*mapBounds[1], *player)) {
		player->Move(0.f, -moveValue * deltaTime);
	}
	if (sat->collisionSAT(*mapBounds[2], *player)) {
		player->Move(moveValue * deltaTime, 0.f);
	}
	if (sat->collisionSAT(*mapBounds[3], *player)) {
		player->Move(-moveValue * deltaTime, 0.f);
	}
}

void PlayState::Render(sf::RenderTarget* target)
{
	target->draw(map);
	for (size_t i = 0; i < itemVect.size(); i++) {
		itemVect[i]->Render(target);
	}
	player->Render(target);
	for (size_t i = 0; i < enemiesVect.size(); i++) {
		enemiesVect[i]->Render(target);
	}
	for (size_t i = 0; i < 4; i++) {
		target->draw(mapBoundsBlack[i]);
	}
	for (size_t i = 0; i < 4; i++) {
		mapBounds[i]->Render(target);
	}
	if (this->endGame == true) {
		window->setMouseCursorVisible(true);
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color(0, 0, 0, 128));
		rect.setSize(sf::Vector2f(1920.f, 1080.f));
		rect.setPosition((*window).mapPixelToCoords(sf::Vector2i(0, 0)));
		target->draw(rect);
		target->draw(scoreText);
		target->draw(gameOverText);
		target->draw(playerNameText);
	}
	else { 
		gui->Display(target); 
		target->draw(crosshair);
	}
	target->setView(*view);
}
