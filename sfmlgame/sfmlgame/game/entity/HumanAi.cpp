#include "HumanAi.h"
#include <iostream>


HumanAi::HumanAi(int nid): Person(nid),
brain(this), brainRegulator(1.f)
{
	realType = Type::HumanAi;
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
	if(brainRegulator.isReady(dt))
		brain.update(brainRegulator.getDelta());
	//brain.update(dt);

	updateSkeleton(dt);
	updateBody();
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
	packet << getHealth();
}

void HumanAi::readInformation(sf::Packet & packet)
{
	Vec2f newpos;
	Vec2f newspeed;
	Vec2f look;
	Vec2f control;
	int newhp;

	packet >> newpos >> newspeed >> look >> control >> newhp;

	setBodyPos(newpos);
	speed = newspeed;
	setBodySpeed(newspeed);
	lookPosition = look;
	moveControl = control;
	health = newhp;
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