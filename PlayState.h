#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>

#include "State.h"
#include "PauseMenu.h"
#include "Player.h"
#include "Enemy.h"
#include "GUI.h"
#include "SAT.h"
#include "Item.h"
#include "MapBound.h"

class PlayState : public State
{
private: //Variables
	float difficulty;
	int ammoInMag, ammoRemained;
	float playerHP, playerPower = 0;
	float difficultyDelay, clickDelay, displayUseItemDelay, enemySpawnDelay, itemSpawnDelay, canShootTime;
	int score, ItemType;
	bool isEndtoMain;
	bool endGame;
	bool isUseItem, canShoot;

	typedef struct Data {
		char name[26];
		int score;
	} Data;

	std::string weaponType;
	std::string playerNameStr;
	std::vector<Enemy*> enemiesVect;
	std::vector<Item*> itemVect;
	MapBound* mapBounds[4];
	sf::RectangleShape mapBoundsBlack[4];

	sf::Text playerNameText;
	sf::Text gameOverText;
	sf::Text scoreText;
	sf::Font font;
	sf::Sprite map;
	sf::Sprite crosshair;

	bool isSadMusicOn;
	sf::Music sadMusic;
	sf::Sound enemyDeadSound;
	sf::Sound pickUpSound;

	Player* player;
	ResourceManager* resourceManager;
	GUI* gui;
	SAT* sat;

public: //Variables

private: //Functions

public: //Functions
	PlayState(sf::RenderWindow* window, ResourceManager* resourceManager, std::stack<State*>* statesPtr);
	virtual ~PlayState();

	void InitMap();

	void SpawnEnemy(float deltaTime);
	void EnemyUpdate(float deltaTime);
	void SpawnItem(float deltaTime);
	void ItemUpdate(float delatTime);
	void Collsion(float deltaTime);

	void WriteOnToFile(Data* d);
	void ReadFromFile(Data* d);
	static int Compare(const void* a, const void* b);

	void SaveScore();
	void GetPlayerName();
	void ToNextState(int stateNum);
	void Update(float deltaTime); //Definitive virtual function??
	void Render(sf::RenderTarget* target = nullptr);
};

#endif PLAYSTATE_H
