#include "Regulator.h"



Regulator::Regulator(float interval)
{
	this->interval = interval;
}


Regulator::~Regulator()
{
}

bool Regulator::isReady(float dt)
{
	delta += dt;
	if (delta >= interval)
		return true;

	return false;
}

float Regulator::getDelta()
{
	float deltaCopy = delta;
	delta = GlobalRandom::range(0.0f, interval/2.f);
	return deltaCopy;
}
