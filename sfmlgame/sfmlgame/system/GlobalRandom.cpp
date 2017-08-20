#include "GlobalRandom.h"



GlobalRandom::GlobalRandom():gen(rd())
{
}


GlobalRandom::~GlobalRandom()
{
}

float GlobalRandom::range(float from, float to)
{
	std::uniform_real_distribution<> dist(from, to);

	return dist(getInstance().gen);
}

GlobalRandom & GlobalRandom::getInstance()
{
	static GlobalRandom a;
	return a;
}
