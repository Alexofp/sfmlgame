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

	virtual MultiplayerMessage writeInformation();
	virtual void readInformation(MultiplayerMessage& message);
	MultiplayerMessage spawnMessage();

private:
	Vec2f targetPos;
};

