#pragma once
#include "GlobalRandom.h"

class Regulator
{
public:
	Regulator(float interval);
	~Regulator();

	bool isReady(float dt);
	float getDelta();
private:
	float delta;
	float interval;
};

