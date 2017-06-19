#include "Person.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"
#include "GameWindow.h"
#include "Settings.h"
#include "AnimationManager.h"


Person::Person(int nid) :AliveEntity(nid)
{
	walkSpeed = 1000.f;
	acceleration = 1000.f;
	maxSpeed = 1000.f;
	speed = Vec2f(0, 0);
	currentAnimation = 0;

	skeleton.playerSkeleton();

	state = "idle";

	playAnimation("person_idle");
}


Person::~Person()
{
}

void Person::init()
{
	body = world->getPhysicsWorld().createCircle(getPos(), 40.f);
}

void Person::draw()
{
	skeleton.draw();
	if (Settings::getBool("render", "debug", false))
		skeleton.debugDraw();
}

void Person::updateSkeleton(float dt)
{
	targetSpeed = Vec2f::mul(moveControl, walkSpeed);
	updateMove(dt);

	if (speed.len() > 10)
	{
		playAnimation("person_walk");
		skeleton.setSpeed(speed.len()/200.f);
	}
	else
	{
		playAnimation("person_idle");
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
}

void Person::playAnimation(std::string animName)
{
	Animation* anim = AnimationManager::getAnimation(animName);

	if (anim != currentAnimation)
	{
		currentAnimation = anim;
		skeleton.playAnimation(anim);
	}
}
