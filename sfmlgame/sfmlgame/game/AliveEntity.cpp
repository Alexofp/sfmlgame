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

	if (speed.len() > 0.1)
	{
		skeleton.setAng(speed.getAngle());
	}

	skeleton.update(dt);
	updateBody();
}

void AliveEntity::setTarget(Vec2f target)
{
	targetSpeed = target;
}
