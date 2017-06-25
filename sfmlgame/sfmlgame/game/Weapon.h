#pragma once
#include <string>

class Weapon
{
public:
	Weapon();
	~Weapon();

//private:
	std::string name;
	std::string textName;
	std::string attackType;
	std::string attackAnimation;
	std::string skin;
	std::string idleAnimation;
	std::string walkAnimation;
};

