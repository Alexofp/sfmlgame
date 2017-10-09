#include "HumanAiBrain.h"
#include "Vec2f.h"
#include "HumanAi.h"


HumanAiBrain::HumanAiBrain(HumanAi* bot)
{
	this->bot = bot;
	targetPos = bot->getPos();
}


HumanAiBrain::~HumanAiBrain()
{
}

void HumanAiBrain::update(float dt)
{
	timer -= dt;
	if (timer <= 0.f || Vec2f::distance(targetPos, bot->getPos()) < 10.f)
	{
		timer = 3.f + rand() % 3;
		int size = 1000;
		targetPos = Vec2f::add(Vec2f(rand() % size - size / 2, rand() % size - size / 2), bot->getPos());
	}
	bot->moveTo(targetPos);

	if (rand() % 100 > 98)
		bot->attack();

	bot->lookAt(targetPos);
}
