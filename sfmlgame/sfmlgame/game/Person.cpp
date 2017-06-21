#include "Person.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"
#include "GameWindow.h"
#include "Settings.h"
#include "AnimationManager.h"
#include "Server.h"

Person::Person(int nid) :AliveEntity(nid)
{
	walkSpeed = 3000.f;
	acceleration = 1000.f;
	maxSpeed = 3000.f;
	speed = Vec2f(0, 0);
	currentAnimation = 0;

	skeleton.playerSkeleton();

	state = "idle";

	currentPriority = 0;
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
	if (getCurrentAnimation() == "person_hit")
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
}

void Person::playAnimation(std::string animName, int priority)
{
	Animation* anim = AnimationManager::getAnimation(animName);

	if (priority >= currentPriority || skeleton.getProgress() >= 1.f)
	{
		currentPriority = priority;

		if (anim != currentAnimation)
		{
			currentAnimationName = animName;
			currentAnimation = anim;
			skeleton.playAnimation(anim);
		}
	}
}

void Person::playAttack()
{
	playAnimation("person_hit", 1);
}

std::string Person::getCurrentAnimation()
{
	if (currentAnimation == 0)
		return "";

	return currentAnimationName;
}

void Person::attack()
{
	NetEvent event(getNid(), getNid(), "attack");
	sendEvent(event);
}

void Person::handleEvent(int fromId, std::string type, sf::Packet & packet)
{
	AliveEntity::handleEvent(fromId, type, packet);

	if (type == "attack" && fromId == getNid())
	{
		playAttack();

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

void Person::onDeath()
{
	skeleton.setScale( 0.f );
}
