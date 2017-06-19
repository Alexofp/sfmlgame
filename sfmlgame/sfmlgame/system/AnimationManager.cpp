#include "AnimationManager.h"



AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}

void AnimationManager::loadAnimation(std::string name, std::string path)
{
	Animation* anim = new Animation();
	anim->loadFromFile(path);

	getInstance().animations[name].reset(anim);
}

Animation * AnimationManager::getAnimation(std::string name)
{
	return getInstance().animations.at(name).get();
}

AnimationManager & AnimationManager::getInstance()
{
	static AnimationManager manager;
	return manager;
}
