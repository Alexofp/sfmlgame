#include "Person.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"
#include "GameWindow.h"
#include "Settings.h"
#include "AnimationManager.h"
#include "Server.h"
#include "WeaponManager.h"
#include "GlobalRandom.h"

Person::Person(int nid) :AliveEntity(nid)
{
	walkSpeed = 3000.f;
	acceleration = 1000.f;
	maxSpeed = 3000.f;
	speed = Vec2f(0, 0);
	currentAnimation = 0;
	attackTimer = 0.0f;

	skeleton.playerSkeleton();
	legsskeleton.legsSkeleton();
	Skin legSkin;
	legSkin.loadFromFile("resources/legsskin.json");
	legsskeleton.setSkin(legSkin);
	legsskeleton.setScale(0.5f);

	state = "idle";

	currentPriority = 0;
	playAnimation("person_idle");

	baseSkin.loadFromFile("resources/skin.json");

	setWeapon("ak74");
}


Person::~Person()
{
}

void Person::init()
{
	body = world->getPhysicsWorld().createCircle(getPos(), 40.f);
	body->setEntity(this);
}

void Person::draw()
{
	legsskeleton.draw();
	skeleton.draw();
	if (Settings::getBool("render", "debug", false))
		skeleton.debugDraw();
}

void Person::updateSkeleton(float dt)
{
	legsskeleton.update(dt);
	legsskeleton.setPos(getPos());

	targetSpeed = Vec2f::mul(moveControl, walkSpeed);
	updateMove(dt);

	if (speed.len() > 10)
	{
		playAnimation(weapon.info.walkAnimation);
		skeleton.setSpeed(speed.len()/400.f);

		legsskeleton.setAng(speed.getAngle());
		legsskeleton.setSpeed(speed.len() / 400.f);

		
		Animation* anim = AnimationManager::getAnimation("legs_walk");
		if(legsskeleton.getAnimation() != anim)
			legsskeleton.playAnimation(anim);
	}
	else
	{
		//playAnimation("person_idle");
		playAnimation(weapon.info.idleAnimation);
		Animation* anim = AnimationManager::getAnimation("legs_idle");
		legsskeleton.playAnimation(anim);
		skeleton.setSpeed(1.f);

		legsskeleton.setAng(skeleton.getAng());
	}
	if (getCurrentAnimation() == weapon.info.attackAnimation)
	{
		skeleton.setSpeed(1.f);
	}

	float targetAngle = Vec2f::sub(lookPosition, getPos()).getAngle();
	while (targetAngle > 180.f)
		targetAngle -= 360.f;
	while (targetAngle < -180.f)
		targetAngle += 360.f;
	float currentAngle = skeleton.getAng();
	while (currentAngle > 180.f)
		currentAngle -= 360.f;
	while (currentAngle < -180.f)
		currentAngle += 360.f;
	float delta = targetAngle - currentAngle;
	if (delta > 180)
	{
		targetAngle -= 360.f;
	}
	if (delta < -180)
	{
		targetAngle += 360.f;
	}

	skeleton.setAng(currentAngle + (targetAngle - currentAngle)*dt*10.f);

	skeleton.update(dt);

	skeleton.setPos(getPos());

	if(attackTimer >= 0)
		attackTimer -= dt;
}

void Person::setWeapon(std::string name)
{
	WeaponData weapon;
	weapon.name = name;
	weapon.info = WeaponManager::getWeapon(name);

	this->weapon = weapon;

	Skin weaponSkin;
	weaponSkin.loadFromFile("resources/"+weapon.info.skin);

	Skin finalSkin = baseSkin;
	finalSkin.applySkin(weaponSkin);

	skeleton.setSkin(finalSkin);
}

std::string Person::getWeaponName()
{
	return weapon.name;
}

void Person::playAnimation(std::string animName, int priority, bool playAgain)
{
	Animation* anim = AnimationManager::getAnimation(animName);

	if (priority >= currentPriority || skeleton.getProgress() >= 1.f)
	{
		currentPriority = priority;

		if (playAgain)
		{
			currentAnimationName = animName;
			currentAnimation = anim;
			skeleton.playAnimation(anim);
		}else if (anim != currentAnimation)
		{
			currentAnimationName = animName;
			currentAnimation = anim;
			skeleton.playAnimation(anim);
		}
	}
}

void Person::playAttack()
{
	playAnimation(weapon.info.attackAnimation, 1, true);
}

std::string Person::getCurrentAnimation()
{
	if (currentAnimation == 0)
		return "";

	return currentAnimationName;
}

void Person::attack()
{
	if (attackTimer > 0.0)
		return;

	if (weapon.info.attackType == "bullet")
	{
		for (int i = 0; i < weapon.info.bulletsPerShot;i++)
		{
			float randAng = GlobalRandom::range(-weapon.info.dispersion, weapon.info.dispersion);
			float randSpeed = GlobalRandom::range(weapon.info.bulletSpeed - weapon.info.bulletSpeedSpread, weapon.info.bulletSpeed + weapon.info.bulletSpeedSpread);

			NetEvent event(getNid(), getNid(), "fireBullet");
			event.data << getShootingPos() << (getShootingAng() + randAng) << randSpeed << weapon.info.bulletAliveTime;
			sendEvent(event);
		}

		NetEvent event(getNid(), getNid(), "attack");
		sendEvent(event);
	}else if (weapon.info.attackType == "melee")
	{
		NetEvent event(getNid(), getNid(), "attack");
		sendEvent(event);
	}


	attackTimer = weapon.info.attackSpeed;
}

Vec2f Person::getShootingPos()
{
	float ang = skeleton.getAng();
	return Vec2f::add(getPos(), Vec2f::fromAngle(ang, 100.f));
}

float Person::getShootingAng()
{
	float ang = skeleton.getAng();
	return ang;
}

void Person::handleEvent(int fromId, std::string type, sf::Packet & packet)
{
	AliveEntity::handleEvent(fromId, type, packet);

	if (type == "fireBullet" && fromId == getNid())
	{
		if (weapon.info.attackType == "bullet")
		{
			Vec2f shootingPos;
			float ang;
			float speed;
			float bulletAliveTimer;
			packet >> shootingPos >> ang >> speed >> bulletAliveTimer;
			world->fireBullet(shootingPos, Vec2f::fromAngle(ang, speed), bulletAliveTimer);
		}
	}

	if (type == "attack" && fromId == getNid())
	{
		playAttack();

		if (weapon.info.attackType == "melee")
		{
			if (Server::isInServer())
			{
				auto closeEntities = world->findInRange(getPos(), 140.f);
				for (Entity* ent : closeEntities)
				{
					if (ent != this)
					{
						NetEvent event(getNid(), ent->getNid(), "hurt");
						sendEvent(event);
					}
				}
			}
		}
	}
}

void Person::onDeath()
{
	skeleton.setScale( 0.f );
}
