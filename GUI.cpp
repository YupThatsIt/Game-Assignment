#include "GUI.h"

GUI::GUI(ResourceManager* resourceManager)
{
	this->resourceManager = resourceManager;
	this->roboto = resourceManager->getFont("Roboto");

	this->HP.setFont(roboto);
	this->HP.setFillColor(sf::Color::White);
	this->HP.setCharacterSize(60);

	this->Ammo.setFont(roboto);
	this->Ammo.setFillColor(sf::Color::White);
	this->Ammo.setCharacterSize(48);

	this->Score.setFont(roboto);
	this->Score.setFillColor(sf::Color::White);
	this->Score.setCharacterSize(48);

	this->Item1.setFont(roboto);
	this->Item1.setFillColor(sf::Color::White);
	this->Item1.setCharacterSize(48);

	this->Item2.setFont(roboto);
	this->Item2.setFillColor(sf::Color(255, 255, 255, 128));
	this->Item2.setCharacterSize(40);

	this->ItemUsedPopUp.setFont(roboto);
	this->ItemUsedPopUp.setFillColor(sf::Color::White);
	this->ItemUsedPopUp.setCharacterSize(20);

	this->weapon1.setScale(1.f, 1.f);
	this->weapon2.setColor(sf::Color(0, 0, 0, 128));
	this->weapon2.setScale(0.5f, 0.5f);
}

GUI::~GUI()
{
}

void GUI::UpdateAmmo(int* ammoInMag, int* ammoRemained, std::string* type, std::string othertype, sf::Vector2f pos)
{
	this->Ammo.setPosition(pos);
	std::stringstream ss;
	this->weapon1.setPosition(sf::Vector2f(pos.x, pos.y + 80));
	this->weapon2.setPosition(sf::Vector2f(pos.x, pos.y + 200));
	if (*type == "AK") {
		ss << "AK-47";
		this->weapon1.setTexture(resourceManager->getTexture("AKItem"));
	}
	else if (*type == "SG") {
		ss << "Shotgun";
		this->weapon1.setTexture(resourceManager->getTexture("SGItem"));
	}
	else {
		ss << "Handgun";
		this->weapon1.setTexture(resourceManager->getTexture("HGItem"));
	}

	if (othertype == "AK") {
		this->weapon2.setTexture(resourceManager->getTexture("AKItem"));
	}
	else if (othertype == "SG") {
		this->weapon2.setTexture(resourceManager->getTexture("SGItem"));
	}
	else {
		this->weapon2.setTexture(resourceManager->getTexture("HGItem"));
	}

	ss << " : " << *ammoInMag << " / ";
	if (*ammoRemained == -1) {
		ss << "-";
	}
	else {
		ss << *ammoRemained;
	}
	std::string str = ss.str();
	this->Ammo.setString(str);
}

void GUI::UpdatePlayerProp(float *HP, float *energy, sf::Vector2f pos)
{
	this->HP.setPosition(pos);
	std::stringstream ss;
	ss << "HP : " << *HP;
	std::string str = ss.str();
	this->HP.setString(str);
}

void GUI::UpdateScore(int *score, sf::Vector2f pos) 
{
	this->Score.setPosition(pos);
	std::stringstream ss;
	ss << "Score : " << *score;
	std::string str = ss.str();
	this->Score.setString(str);
}

void GUI::UpdateItem(int curItemType, int otherItemType, sf::Vector2f pos)
{
	this->Item1.setPosition(pos);
	this->Item2.setPosition(sf::Vector2f(pos.x, pos.y + 50));
	std::stringstream ss;
	switch (curItemType) {
	case 1:
		ss << "> First Aid";
		break;
	case 2:
		ss << "> Ammo Box";
		break;
	case 3:
		ss << "> Nuke";
		break;
	case 4:
		ss << "> Vaccine";
		break;
	default:
		ss << "> None";
		break;
	}
	std::string str = ss.str();
	this->Item1.setString(str);
	ss.str("");
	ss.clear();
	switch (otherItemType) {
	case 1:
		ss << " First Aid";
		break;
	case 2:
		ss << " Ammo Box";
		break;
	case 3:
		ss << " Nuke";
		break;
	case 4:
		ss << " Vaccine";
		break;
	default:
		ss << " None";
		break;
	}
	str = ss.str();
	this->Item2.setString(str);
}

void GUI::UseItemEffect(int itemType, int showValue, sf::Vector2f pos)
{
	if (showValue == 1) {
		this->ItemUsedPopUp.setPosition(pos);
		std::stringstream ss;
		switch (itemType) {
		case 1:
			ss << "Bandage Used\n" <<
				  "  + 50 HP  ";
			break;
		case 2:
			ss << "Ammo Box Used\n" <<
			      "  + 3 Mags  ";
			break;
		case 3:
			ss << "Nuke Used\n" <<
				  " KABOOM ";
			break;
		case 4:
			ss << "Vaccine Used\n" <<
				  "   Immuned   ";
			break;
		default:
			//Nothing been used
			break;
		}
		std::string str = ss.str();
		this->ItemUsedPopUp.setString(str);
	}
	else {
		std::string str = "";
		this->ItemUsedPopUp.setString(str);
	}
}

void GUI::Display(sf::RenderTarget* target)
{
	target->draw(this->weapon1);
	target->draw(this->weapon2);
	target->draw(this->Score);
	target->draw(this->HP);
	target->draw(this->Ammo);
	target->draw(this->Item1);
	target->draw(this->Item2);
	target->draw(this->ItemUsedPopUp);
}
