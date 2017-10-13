#pragma once
#include <string>

struct Weapon
{
	std::string name;
	std::string textName;
	std::string attackType;
	std::string attackAnimation;
	std::string skin;
	std::string idleAnimation;
	std::string walkAnimation;
	float baseDamage;
	float damagePerLevelPercent;
	float bulletSpeed;
	float dispersion;
	bool autoFire;
	float attackSpeed;
	int bulletsPerShot;
	float bulletAliveTime;
	float bulletSpeedSpread;
	std::string usesAmmo;
	int clipSize;
	int ammoPerShot;
};

