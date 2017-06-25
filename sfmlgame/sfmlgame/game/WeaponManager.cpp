#include "WeaponManager.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;


WeaponManager::WeaponManager()
{
}


WeaponManager::~WeaponManager()
{
}

void WeaponManager::loadFromFile(std::string path)
{
	std::ifstream file(path);
	json jsonData;
	file >> jsonData;

	for (auto& item : jsonData)
	{
		std::string name = item["name"].get<std::string>();
		std::string textName = item["textName"].get<std::string>();
		std::string attackType = item["attackType"].get<std::string>();
		std::string attackAnimation = item["attackAnimation"].get<std::string>();
		std::string skin = item["skin"].get<std::string>();
		std::string idleAnimation = item["idleAnimation"].get<std::string>();
		std::string walkAnimation = item["walkAnimation"].get<std::string>();

		Weapon weapon;
		weapon.name = name;
		weapon.textName = textName;
		weapon.attackType = attackType;
		weapon.attackAnimation = attackAnimation;
		weapon.skin = skin;
		weapon.idleAnimation = idleAnimation;
		weapon.walkAnimation = walkAnimation;

		getInstance().weapons[name] = weapon;
	}
}

Weapon WeaponManager::getWeapon(std::string name)
{
	return getInstance().weapons.at(name);
}

WeaponManager & WeaponManager::getInstance()
{
	static WeaponManager manager;
	return manager;
}
