#include "Animation.h"

Animation::Animation(ResourceManager* resourceManager)
{
	this->resourceManager = resourceManager;
}

Animation::~Animation()
{
	//delete this->resourceManager;
}

sf::Texture& Animation::GetAnimFrame(std::string animName, int animFrame)
{
	std::stringstream ss;
	ss << animName << animFrame;
	std::string str = ss.str();
	textureFrame = this->resourceManager->getTexture(str);
	return textureFrame;
}
