#pragma once
#include "AliveEntity.h"
#include "Weapon.h"

class Person :
	public AliveEntity
{
public:
	struct WeaponData
	{
		std::string name;
		Weapon info;
	};

	Person(int nid = -1);
	virtual ~Person();

	virtual void init();
	virtual void draw();
	void updateSkeleton(float dt);
	void setWeapon(std::string name);
	std::string getWeaponName();

	void playAnimation(std::string anim, int priority = 0, bool playAgain = false);
	void playAttack();
	std::string getCurrentAnimation();
	void attack();
	Vec2f getShootingPos();
	float getShootingAng();

	bool lookAt(Vec2f pos);
	bool moveTo(Vec2f pos);

	virtual void handleEvent(int fromId, std::string type, sf::Packet& packet);
	virtual void onDeath();

protected:
	AnimatedSkeleton skeleton;
	AnimatedSkeleton legsskeleton;
	Animation* currentAnimation;
	std::string currentAnimationName;
	Vec2f moveControl;
	float walkSpeed;
	Vec2f lookPosition;
	std::string state;
	int currentPriority;
	WeaponData weapon;
	Skin baseSkin;
	float attackTimer;
};

