#pragma once
#include "Vec2f.h"
#include <SFML/Network.hpp>

class Entity
{
public:
	enum class SyncType
	{
		Entity,
		Player
	};

	enum class Type
	{
		Entity,
		Player
	};

	Entity(int nid = -1);
	~Entity();

	virtual void update(float dt) = 0;
	virtual void localUpdate(float dt) = 0;
	virtual void draw() = 0;

	void setPos(Vec2f pos);
	void setSize(Vec2f size);
	void setAng(float ang);

	Vec2f getPos();
	Vec2f getSize();
	float getAng();

	virtual void writeInformation(sf::Packet& packet);
	virtual void readInformation(sf::Packet& packet);
	int getNid();
	SyncType getSyncType();
	Type getType();
private:
	Vec2f pos;
	Vec2f size;
	float angle;
	int nid;
protected:
	SyncType type;
	Type realType;
};

