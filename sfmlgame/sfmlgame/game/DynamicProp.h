#pragma once
#include "PhysicsEntity.h"
#include "SimpleSprite.h"

class DynamicProp :
	public PhysicsEntity
{
public:
	DynamicProp(int nid = -1);
	~DynamicProp();

	void init();
	void update(float dt);
	void localUpdate(float dt);
	void draw();

	MultiplayerMessage writeInformation();
	void readInformation(MultiplayerMessage& message);
	MultiplayerMessage spawnMessage();
private:
	SimpleSprite sprite;
	Vec2f speed;
};

