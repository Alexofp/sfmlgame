#pragma once
#include "Vec2f.h"

class HumanAi;

class HumanAiBrain
{
public:
	HumanAiBrain(HumanAi* bot);
	virtual ~HumanAiBrain();

	void update(float dt);

private:
	HumanAi* bot;

	Vec2f targetPos;
	float timer;
};

