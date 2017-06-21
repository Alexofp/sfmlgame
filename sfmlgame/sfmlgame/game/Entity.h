#pragma once
#include "Vec2f.h"
#include <SFML/Network.hpp>
#include "SharedMultiplayer.h"
#include "NetEvent.h"

class GameWorld;

class Entity
{
public:
	enum class Type
	{
		Entity,
		Player,
		DynamicProp,
		HumanAi
	};

	Entity(int nid = -1);
	~Entity();

	virtual void update(float dt) = 0;
	virtual void localUpdate(float dt) = 0;
	virtual void draw() = 0;
	virtual void init() = 0;

	void setPos(Vec2f pos);
	void setSize(Vec2f size);
	void setAng(float ang);

	Vec2f getPos();
	Vec2f getSize();
	float getAng();

	virtual void writeInformation(sf::Packet& packet);
	virtual void readInformation(sf::Packet& packet);
	//virtual MultiplayerMessage spawnMessage();
	virtual void writeSpawn(sf::Packet& packet);
	virtual void readSpawn(sf::Packet& packet);

	void sendEvent(NetEvent event);
	virtual void handleEvent(int fromId, std::string type, sf::Packet& packet);
	int getNid();
	Type getType();

	void add(GameWorld* world);
private:
	Vec2f pos;
	Vec2f size;
	float angle;
	int nid;
protected:
	Type realType;
	GameWorld* world;
};

