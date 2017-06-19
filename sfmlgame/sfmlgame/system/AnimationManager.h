#pragma once
#include "Animation.h"
#include <unordered_map>
#include <string>
#include <memory>

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	static void loadAnimation(std::string name, std::string path);
	static Animation* getAnimation(std::string name);

private:
	static AnimationManager& getInstance();

	std::unordered_map<std::string, std::unique_ptr<Animation> > animations;
};

