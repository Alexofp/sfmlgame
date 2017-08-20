#pragma once
#include <random>

class GlobalRandom
{
public:
	GlobalRandom();
	virtual ~GlobalRandom();

	static float range(float from, float to);

private:
	std::random_device rd;
	std::mt19937 gen;

	static GlobalRandom& getInstance();
};

