#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

#include "ResourceManager.h"

class GUI
{
private: //Variables
	ResourceManager* resourceManager;
	sf::Text HP;
	sf::Text Ammo;
	sf::Text Score;
	sf::Text Item1;
	sf::Text Item2;
	sf::Text ItemUsedPopUp;

	sf::Sprite weapon1;
	sf::Sprite weapon2;

	sf::Font roboto;
	sf::Font AmmoFont;

public: //Variables

private: //Functions

public: //Functions
	GUI(ResourceManager* resourceManager);
	virtual ~GUI();

	void UpdateAmmo(int *ammoInMag, int *ammoRemained, std::string *type, std::string othertype, sf::Vector2f pos);
	void UpdatePlayerProp(float *HP, float *energy, sf::Vector2f pos);
	void UpdateScore(int* score, sf::Vector2f pos);
	void UpdateItem(int itemType, int otherItemType, sf::Vector2f pos);
	void UseItemEffect(int itemType, int showValue, sf::Vector2f pos);
	void Display(sf::RenderTarget* target);
};

#endif GUI_H

