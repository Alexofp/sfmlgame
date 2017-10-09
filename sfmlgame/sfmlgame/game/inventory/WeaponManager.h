#pragma once
#include <unordered_map>
#include <string>
#include "Weapon.h"

class WeaponManager
{
public:
	WeaponManager();
	~WeaponManager();

	static void loadFromFile(std::string path);
	static Weapon getWeapon(std::string name);

private:
	static WeaponManager& getInstance();

	std::unordered_map<std::string, Weapon> weapons;
};

