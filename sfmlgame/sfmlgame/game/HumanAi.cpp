#include "HumanAi.h"
#include <iostream>


HumanAi::HumanAi(int nid): Person(nid)
{
	realType = Type::HumanAi;

	timer = 0.f;
}


HumanAi::~HumanAi()
{
}

void HumanAi::init()
{
	Person::init();
}

void HumanAi::update(float dt)
{
	lookPosition = targetPos;

	updateSkeleton(dt);
	updateBody();


	timer -= dt;
	if (timer <= 0.f || Vec2f::distance(targetPos, getPos()) < 10.f)
	{
		timer = 3.f+rand()%3;
		int size = 1000;
		targetPos = Vec2f::add(Vec2f(rand() % size - size/2, rand() % size - size/2), getPos());
	}
	moveControl = Vec2f::sub(targetPos, getPos()).normalized();

	if (rand() % 100 > 98)
		attack();
}

void HumanAi::localUpdate(float dt)
{
	updateSkeleton(dt);
	updateBody();
}

void HumanAi::draw()
{
	Person::draw();
}

void HumanAi::writeInformation(sf::Packet & packet)
{
	packet << getBodyPos();
	packet << getBodySpeed();
	packet << lookPosition;
	packet << moveControl;
}

void HumanAi::readInformation(sf::Packet & packet)
{
	Vec2f newpos;
	Vec2f newspeed;
	Vec2f look;
	Vec2f control;

	packet >> newpos >> newspeed >> look >> control;

	setBodyPos(newpos);
	speed = newspeed;
	setBodySpeed(newspeed);
	lookPosition = look;
	moveControl = control;
}

void HumanAi::writeSpawn(sf::Packet & packet)
{
	packet << getBodyPos();
	packet << getBodySpeed();
	packet << lookPosition;
}

void HumanAi::readSpawn(sf::Packet & packet)
{
	Vec2f newpos;
	Vec2f newspeed;
	Vec2f look;

	packet >> newpos >> newspeed >> look;

	setBodyPos(newpos);
	speed = newspeed;
	setBodySpeed(newspeed);
	lookPosition = look;
}