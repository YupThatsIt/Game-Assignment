#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	loadTexture();
	loadSound();
	loadFont();
}

void ResourceManager::loadTexture() {
	if (!playerAK.loadFromFile("Resources/Texture/Player/survivor-idle_rifle_0.png")) {}
	textureUmap["PlayerAK"] = playerAK;

	if (!playerSG.loadFromFile("Resources/Texture/Player/survivor-idle_shotgun_0.png")) {}
	textureUmap["PlayerSG"] = playerSG;

	if (!playerPistol.loadFromFile("Resources/Texture/Player/survivor-idle_handgun_0.png")) {}
	textureUmap["PlayerHG"] = playerPistol;

	if (!enemy.loadFromFile("Resources/Texture/skeleton-attack_0.png")) {}
	textureUmap["Enemy"] = enemy;

	if (!bullet.loadFromFile("Resources/Texture/Bullet.png")) {}
	textureUmap["Bullet"] = bullet;

	if (!map.loadFromFile("Resources/Texture/Map/Map.png")) {}
	textureUmap["Map"] = map;

	if (!crosshair.loadFromFile("Resources/Texture/Crosshair.png")) {}
	textureUmap["Crosshair"] = crosshair;

	if (!item[0].loadFromFile("Resources/Texture/Item/Item1.png")) { std::cout << "Failed to load item 1\n"; }
	textureUmap["Firstaid"] = item[0];
	if (!item[1].loadFromFile("Resources/Texture/Item/Item2.png")) { std::cout << "Failed to load item 2\n"; }
	textureUmap["Ammo"] = item[1];
	if (!item[2].loadFromFile("Resources/Texture/Item/Item3.png")) { std::cout << "Failed to load item 3\n"; }
	textureUmap["Nuke"] = item[2];
	if (!item[3].loadFromFile("Resources/Texture/Item/Item4.png")) { std::cout << "Failed to load item 4\n"; }
	textureUmap["Vaccine"] = item[3];
	if (!item[4].loadFromFile("Resources/Texture/Item/AKItemGlow.png")) { std::cout << "Failed to load item 5\n"; }
	textureUmap["AKItem"] = item[4];
	if (!item[5].loadFromFile("Resources/Texture/Item/SGItemGlow.png")) { std::cout << "Failed to load item 6\n"; }
	textureUmap["SGItem"] = item[5];

	if (!mapBounds[0].loadFromFile("Resources/Texture/Map/MapBoundTop.png")) { std::cout << "Failed to load mapBounds 1\n"; }
	textureUmap["MapBoundTop"] = mapBounds[0];
	if (!mapBounds[1].loadFromFile("Resources/Texture/Map/MapBoundBottom.png")) { std::cout << "Failed to load mapBounds 2\n"; }
	textureUmap["MapBoundBottom"] = mapBounds[1];
	if (!mapBounds[2].loadFromFile("Resources/Texture/Map/MapBoundLeft.png")) { std::cout << "Failed to load mapBounds 3\n"; }
	textureUmap["MapBoundLeft"] = mapBounds[2];
	if (!mapBounds[3].loadFromFile("Resources/Texture/Map/MapBoundRight.png")) { std::cout << "Failed to load mapBounds 4\n"; }
	textureUmap["MapBoundRight"] = mapBounds[3];

	if (!backgrounds[0].loadFromFile("Resources/Texture/Backgrounds/MenuBackGround.png")) { std::cout << "Failed to load bg 1\n"; }
	textureUmap["MainmenuBG"] = backgrounds[0];
	if (!backgrounds[1].loadFromFile("Resources/Texture/Backgrounds/LeaderBoard.png")) { std::cout << "Failed to load bg 2\n"; }
	textureUmap["LeaderboardBG"] = backgrounds[1];

	if (!weaponItem[0].loadFromFile("Resources/Texture/Item/AKItem.png")) { std::cout << "Failed to load AKItem\n"; }
	textureUmap["AKItem"] = weaponItem[0];
	if (!weaponItem[1].loadFromFile("Resources/Texture/Item/SGItem.png")) { std::cout << "Failed to load SGItem\n"; }
	textureUmap["SGItem"] = weaponItem[1];
	if (!weaponItem[2].loadFromFile("Resources/Texture/Item/HGItem.png")) { std::cout << "Failed to load HGItem\n"; }
	textureUmap["HGItem"] = weaponItem[2];

	//HgReload
	for (size_t i = 0; i <= 14; i++) {
		std::stringstream ss;
		ss << "Resources/Texture/Player/handgun/reload/survivor-reload_handgun_" << i << ".png";
		std::string str = ss.str();
		if (!playerHGReload[i].loadFromFile(str)) { std::cout << "Failed to load survivor-reload_handgun_" << i << std::endl; }

		ss.str("");
		ss.clear();
		ss << "PlayerHGReload" << i;
		str = ss.str();
		textureUmap[str] = playerHGReload[i];
	}

	//HgShoot
	for (size_t i = 0; i <= 2; i++) {
		std::stringstream ss;
		ss << "Resources/Texture/Player/handgun/shoot/survivor-shoot_handgun_" << i << ".png";
		std::string str = ss.str();
		if (!playerHGShoot[i].loadFromFile(str)) { std::cout << "Failed to load survivor-shoot_handgun_" << i << std::endl; }

		ss.str("");
		ss.clear();
		ss << "PlayerHGShoot" << i;
		str = ss.str();
		textureUmap[str] = playerHGShoot[i];
	}

	//AkReload
	for (size_t i = 0; i <= 19; i++) {
		std::stringstream ss;
		ss << "Resources/Texture/Player/rifle/reload/survivor-reload_rifle_" << i << ".png";
		std::string str = ss.str();
		if (!playerAKReload[i].loadFromFile(str)) { std::cout << "Failed to load survivor-reload_rifle_" << i << std::endl; }

		ss.str("");
		ss.clear();
		ss << "PlayerAKReload" << i;
		str = ss.str();
		textureUmap[str] = playerAKReload[i];
	}

	//AkShoot
	for (size_t i = 0; i <= 2; i++) {
		std::stringstream ss;
		ss << "Resources/Texture/Player/rifle/shoot/survivor-shoot_rifle_" << i << ".png";
		std::string str = ss.str();
		if (!playerAKShoot[i].loadFromFile(str)) { std::cout << "Failed to load survivor-shoot_rifle_" << i << std::endl; }

		ss.str("");
		ss.clear();
		ss << "PlayerAKShoot" << i;
		str = ss.str();
		textureUmap[str] = playerAKShoot[i];
	}

	for (size_t i = 0; i <= 19; i++) {
		std::stringstream ss;
		ss << "Resources/Texture/Player/shotgun/reload/survivor-reload_shotgun_" << i << ".png";
		std::string str = ss.str();
		if (!playerSGReload[i].loadFromFile(str)) { std::cout << "Failed to load survivor-reload_shotgun_" << i << std::endl; }

		ss.str("");
		ss.clear();
		ss << "PlayerSGReload" << i;
		str = ss.str();
		textureUmap[str] = playerSGReload[i];
	}

	for (size_t i = 0; i <= 2; i++) {
		std::stringstream ss;
		ss << "Resources/Texture/Player/shotgun/shoot/survivor-shoot_shotgun_" << i << ".png";
		std::string str = ss.str();
		if (!playerSGShoot[i].loadFromFile(str)) { std::cout << "Failed to load survivor-shoot_shotgun_" << i << std::endl; }

		ss.str("");
		ss.clear();
		ss << "PlayerSGShoot" << i;
		str = ss.str();
		textureUmap[str] = playerSGShoot[i];
	}

	//EnemyWalk
	for (size_t i = 0; i <= 16; i++) {
		std::stringstream ss;
		ss << "Resources/Texture/Zombie/walk/skeleton-move_" << i << ".png";
		std::string str = ss.str();
		if (!enemyWalk[i].loadFromFile(str)) { std::cout << "Failed to load skeleton-move_" << i << std::endl; }

		ss.str("");
		ss.clear();
		ss << "EnemyWalk" << i;
		str = ss.str();
		textureUmap[str] = enemyWalk[i];
	}

	//EnemyAttack
	for (size_t i = 0; i <= 8; i++) {
		std::stringstream ss;
		ss << "Resources/Texture/Zombie/attack/skeleton-attack_" << i << ".png";
		std::string str = ss.str();
		if (!enemyAttack[i].loadFromFile(str)) { std::cout << "Failed to load skeleton-attack_" << i << std::endl; }

		ss.str("");
		ss.clear();
		ss << "EnemyAttack" << i;
		str = ss.str();
		textureUmap[str] = enemyAttack[i];
	}
}

void ResourceManager::loadSound() {
	if (!AKShootSound.loadFromFile("Resources/Sound/AKShootSound.wav")) { std::cout << "Failed to load AKShootSound\n"; }
	soundUmap["AKShootSound"] = AKShootSound;
	if (!AKReloadSound.loadFromFile("Resources/Sound/AKReloadSound.wav")) { std::cout << "Failed to load AKReloadSound\n"; }
	soundUmap["AKReloadSound"] = AKReloadSound;
	if (!HGShootSound.loadFromFile("Resources/Sound/HGShootSound.wav")) { std::cout << "Failed to load HGShootSound\n"; }
	soundUmap["HGShootSound"] = HGShootSound;
	if (!HGReloadSound.loadFromFile("Resources/Sound/HGReloadSound.wav")) { std::cout << "Failed to load HGReloadSound\n"; }
	soundUmap["HGReloadSound"] = HGReloadSound;
	if (!SGShootSound.loadFromFile("Resources/Sound/SGShootSound.wav")) { std::cout << "Failed to load SGShootSound\n"; }
	soundUmap["SGShootSound"] = SGShootSound;
	if (!SGReloadSound.loadFromFile("Resources/Sound/SGReloadSound.wav")) { std::cout << "Failed to load SGReloadSound\n"; }
	soundUmap["SGReloadSound"] = SGReloadSound;
	if (!EmptyGun.loadFromFile("Resources/Sound/EmptyGun.wav")) { std::cout << "Failed to load EmptyGun\n"; }
	soundUmap["EmptyGun"] = EmptyGun;

	if (!PlayerHurt.loadFromFile("Resources/Sound/PlayerHurt.wav")) { std::cout << "Failed to load EmptyGun\n"; }
	soundUmap["PlayerHurt"] = PlayerHurt;

	if (!EnemyDeadSound.loadFromFile("Resources/Sound/EnemyDeadSound.wav")) { std::cout << "Failed to load EnemyHurtDead\n"; }
	soundUmap["EnemyDeadSound"] = EnemyDeadSound;
	if (!EnemyHurtSound[0].loadFromFile("Resources/Sound/EnemyHurtSound1.wav")) { std::cout << "Failed to load EnemyHurtSound1\n"; }
	soundUmap["EnemyHurtSound1"] = EnemyHurtSound[0];
	if (!EnemyHurtSound[1].loadFromFile("Resources/Sound/EnemyHurtSound2.wav")) { std::cout << "Failed to load EnemyHurtSound2\n"; }
	soundUmap["EnemyHurtSound2"] = EnemyHurtSound[1];

	if (!PickUpSound.loadFromFile("Resources/Sound/PickUpSound.wav")) { std::cout << "Failed to load PickUpSound\n"; }
	soundUmap["PickUpSound"] = PickUpSound;
	if (!UseItemSound[0].loadFromFile("Resources/Sound/FirstAidUseSound.wav")) { std::cout << "Failed to load FirstaidSound\n"; }
	soundUmap["FirstaidSound"] = UseItemSound[0];
	if (!UseItemSound[1].loadFromFile("Resources/Sound/AmmoUseSound.wav")) { std::cout << "Failed to load AmmoSound\n"; }
	soundUmap["AmmoSound"] = UseItemSound[1];
	if (!UseItemSound[2].loadFromFile("Resources/Sound/NukeUseSound.wav")) { std::cout << "Failed to load NukeSound\n"; }
	soundUmap["NukeSound"] = UseItemSound[2];
	if (!UseItemSound[3].loadFromFile("Resources/Sound/VaccineInjectionSound.wav")) { std::cout << "Failed to load VaccineSound\n"; }
	soundUmap["VaccineSound"] = UseItemSound[3];
	if (!YesScience.loadFromFile("Resources/Sound/VaccineUseSound.wav")) { std::cout << "Failed to load YesScience\n"; }
	soundUmap["YesScience"] = YesScience;

	if (!ButtonClick.loadFromFile("Resources/Sound/ButtonClick.wav")) { std::cout << "Failed to load ButtonClick\n"; }
	soundUmap["ButtonClick"] = ButtonClick;
}

void ResourceManager::loadFont() {
	if (!font[0].loadFromFile("Resources/Font/Roboto/Roboto-Regular.ttf")) { std::cout << "Failed to load font 1\n"; }
	fontUmap["Roboto"] = font[0];
	if (!font[1].loadFromFile("Resources/Font/zombie-queen/Zombie-Queen.ttf")) { std::cout << "Failed to load font 2\n"; }
	fontUmap["ZombieQueen"] = font[1];
	if (!font[2].loadFromFile("Resources/Font/thedeadarecoming/TheDeadAreComing.ttf")) { std::cout << "Failed to load font 3\n"; }
	fontUmap["TheDeadAreComing"] = font[2];
}

sf::Texture& ResourceManager::getTexture(std::string textureName) {
	return textureUmap[textureName];
}
sf::SoundBuffer& ResourceManager::getSoundBuffer(std::string soundName) {
	return soundUmap[soundName];
}
sf::Font& ResourceManager::getFont(std::string fontName) {
	return fontUmap[fontName];
}
