#include "HumanAi.h"
#include <iostream>


HumanAi::HumanAi(int nid): Person(nid)
{
	realType = Type::HumanAi;

	Skin skin;
	skin.loadFromFile("resources/skin.json");
	skeleton.setSkin(skin);
}


HumanAi::~HumanAi()
{
}

void HumanAi::init()
{
	Person::init();

	targetPos = Vec2f::add(Vec2f(rand() % 200 - 100, rand() % 200 - 100), getPos());
}

void HumanAi::update(float dt)
{
	lookPosition = targetPos;

	updateSkeleton(dt);
	updateBody();

	moveControl = Vec2f::sub(targetPos, getPos()).normalized();
	if (Vec2f::distance(targetPos, getPos()) < 10.f)
	{
		targetPos = Vec2f::add(Vec2f(rand() % 200 - 100, rand() % 200 - 100), getPos());
	}
}

void HumanAi::localUpdate(float dt)
{
	updateBody();
	updateSkeleton(dt);
}

void HumanAi::draw()
{
	Person::draw();
}

MultiplayerMessage HumanAi::writeInformation()
{
	MultiplayerMessage message(MessageType::HumanAiUpdate);
	message.setMessage(new HumanAiUpdateMessage(getBodyPos().x, getBodyPos().y, skeleton.getAng(), getBodySpeed().x, getBodySpeed().y, lookPosition.x, lookPosition.y));

	return message;
}

void HumanAi::readInformation(MultiplayerMessage& message)
{
	if (message.getType() == MessageType::HumanAiUpdate)
	{
		HumanAiUpdateMessage* m = message.getMessage<HumanAiUpdateMessage>();

		setBodyPos(Vec2f(m->x, m->y));
		//setBodyAng(m->ang);
		//skeleton.setAng(m->ang);
		
		speed = Vec2f(m->speedx, m->speedy);
		setBodySpeed(Vec2f(m->speedx, m->speedy));
		lookPosition = Vec2f(m->lookx, m->looky);
	}
}

MultiplayerMessage HumanAi::spawnMessage()
{
	MultiplayerMessage message(MessageType::SpawnHumanAiEntity);
	message.setMessage(new SpawnHumanAiEntityMessage(getNid(), getPos().x, getPos().y));

	return message;
}
