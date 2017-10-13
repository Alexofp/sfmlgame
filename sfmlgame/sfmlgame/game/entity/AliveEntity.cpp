#include "AliveEntity.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"
#include "GameWindow.h"
#include "Settings.h"

AliveEntity::AliveEntity(int nid) :PhysicsEntity(nid)
{
	maxSpeed = 100.f;
	acceleration = 100.f;
	speed = Vec2f();
	Vec2f targetSpeed = Vec2f();
	health = 100;
	maxHealth = 100;
}


AliveEntity::~AliveEntity()
{
}

void AliveEntity::updateMove(float dt)
{
	Vec2f newspeed = targetSpeed;

	if (newspeed.len() > maxSpeed)
	{
		float l = newspeed.len();
		newspeed = Vec2f::mul(newspeed.normalized(), Vec2f(maxSpeed, maxSpeed));
	}

	speed = Vec2f::sub(speed, Vec2f::mul(speed, Vec2f(dt * 5, dt * 5)));
	if (speed.len()<maxSpeed)
		speed = Vec2f::add(speed, Vec2f::mul(newspeed, Vec2f(dt, dt)));

	body->setSpeed(speed);


	updateBody();
}

void AliveEntity::setTarget(Vec2f target)
{
	targetSpeed = target;
}

void AliveEntity::handleEvent(int fromId, std::string type, sf::Packet & packet)
{
	if (type == "hurt")
	{
		health -= 34;
		if (health <= 0)
		{
			onDeath();
		}
	}
}

void AliveEntity::onDeath()
{
}

void AliveEntity::drawHealthBar()
{
	healthBar.setHealth(getHealth());
	healthBar.setMaxHealth(getMaxHealth());

	healthBar.setPos(getPos());
	healthBar.draw();
}

int AliveEntity::getHealth()
{
	return health;
}

int AliveEntity::getMaxHealth()
{
	return maxHealth;
}
