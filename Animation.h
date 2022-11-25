#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <sstream>

#include "ResourceManager.h"

class Animation
{
private:
	sf::Texture textureFrame;
	ResourceManager* resourceManager;

public:

private:

public:
	Animation(ResourceManager* resourceManager);
	~Animation();

	sf::Texture& GetAnimFrame(std::string animName, int animFrame);
};

#endif ANIMATION_H

