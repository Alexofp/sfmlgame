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
		float baseDamage = item["baseDamage"].get<float>();
		float damagePerLevelPercent = item["damagePerLevelPercent"].get<float>();
		int magazineCapacity = item["magazineCapacity"].get<int>();
		float attackSpeed = item["attackSpeed"].get<float>();
		bool autoFire = item["autoFire"].get<bool>();

		Weapon weapon;
		weapon.name = name;
		weapon.textName = textName;
		weapon.attackType = attackType;
		weapon.attackAnimation = attackAnimation;
		weapon.skin = skin;
		weapon.idleAnimation = idleAnimation;
		weapon.walkAnimation = walkAnimation;
		weapon.baseDamage = baseDamage;
		weapon.damagePerLevelPercent = damagePerLevelPercent;
		weapon.magazineCapacity = magazineCapacity;
		weapon.attackSpeed = attackSpeed;
		weapon.autoFire = autoFire;

		if (attackType == "bullet")
		{
			float bulletSpeed = item["bulletSpeed"].get<float>();
			float dispersion = item["dispersion"].get<float>();
			int bulletsPerShot = item["bulletsPerShot"].get<int>();
			float bulletAliveTime = item["bulletAliveTime"].get<float>();
			float bulletSpeedSpread = item["bulletSpeedSpread"].get<float>();

			weapon.bulletSpeed = bulletSpeed;
			weapon.dispersion = dispersion;
			weapon.bulletsPerShot = bulletsPerShot;
			weapon.bulletAliveTime = bulletAliveTime;
			weapon.bulletSpeedSpread = bulletSpeedSpread;
		}

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
