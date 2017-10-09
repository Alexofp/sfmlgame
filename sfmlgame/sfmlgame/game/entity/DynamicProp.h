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

	virtual void writeInformation(sf::Packet& packet);
	virtual void readInformation(sf::Packet& packet);
	virtual void writeSpawn(sf::Packet& packet);
	virtual void readSpawn(sf::Packet& packet);
private:
	SimpleSprite sprite;
	Vec2f speed;
};

