#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager
{
private: //Variables
	//Textures
	std::unordered_map<std::string, sf::Texture> textureUmap;
	sf::Texture playerPistol;
	sf::Texture playerSG;
	sf::Texture playerAK;
	sf::Texture enemy;
	sf::Texture bullet;
	sf::Texture map;
	sf::Texture crosshair;
	sf::Texture weaponItem[3];
	sf::Texture item[6];
	sf::Texture mapBounds[4];
	sf::Texture backgrounds[2];
	sf::Texture playerHGReload[15];
	sf::Texture playerHGShoot[3];
	sf::Texture playerAKReload[20];
	sf::Texture playerAKShoot[3];
	sf::Texture playerSGReload[20];
	sf::Texture playerSGShoot[3];
	sf::Texture enemyWalk[17];
	sf::Texture enemyAttack[9];

	//Sounds
	std::unordered_map<std::string, sf::SoundBuffer> soundUmap;
	sf::SoundBuffer AKReloadSound;
	sf::SoundBuffer AKShootSound;
	sf::SoundBuffer HGReloadSound;
	sf::SoundBuffer HGShootSound;
	sf::SoundBuffer SGReloadSound;
	sf::SoundBuffer SGShootSound;
	sf::SoundBuffer EmptyGun;
	sf::SoundBuffer PlayerHurt;
	sf::SoundBuffer EnemyDeadSound;
	sf::SoundBuffer EnemyHurtSound[2];
	sf::SoundBuffer PickUpSound;
	sf::SoundBuffer UseItemSound[4];
	sf::SoundBuffer YesScience;
	sf::SoundBuffer ButtonClick;

	//Fonts
	std::unordered_map<std::string, sf::Font> fontUmap;
	sf::Font font[3];

public: //Variables

private: //Functions
	void loadTexture(); //All will be call when construct the object
	void loadSound(); //Why don't just load everything in the constructor?? >>> one word >> Organized
	void loadFont();

public: //Functions
	ResourceManager(); //Constructor is public. This is not a full fledge singleton but it should work the same

	sf::Texture& getTexture(std::string textureName);
	sf::SoundBuffer& getSoundBuffer(std::string soundName);
	sf::Font& getFont(std::string fontName);
};

#endif RESOURCEMANAGER_H

