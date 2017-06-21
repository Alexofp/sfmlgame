#pragma once
#include "Person.h"

class HumanAi :	public Person
{
public:
	HumanAi(int nid = -1);
	virtual ~HumanAi();

	void init();
	void update(float dt);
	void localUpdate(float dt);
	void draw();

	virtual void writeInformation(sf::Packet& packet);
	virtual void readInformation(sf::Packet& packet);
	virtual void writeSpawn(sf::Packet& packet);
	virtual void readSpawn(sf::Packet& packet);

private:
	Vec2f targetPos;
	float timer;
};

