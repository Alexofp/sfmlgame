#pragma once
#include "Entity.h"
#include "SimpleSprite.h"
#include "AnimatedSkeleton.h"
#include "Skin.h"
#include "Animation.h"
#include "PhysicsEntity.h"
#include "AliveEntity.h"
#include "Person.h"

class Player: public Person
{
public:
	Player(int nid = -1);
	~Player();

	void init();
	void update(float dt);
	void localUpdate(float dt);
	void draw();
	void setRemote(bool isRemote);

	void setClientId(int clientId);
	int getClientId();

	virtual void writeInformation(sf::Packet& packet);
	virtual void readInformation(sf::Packet& packet);
	virtual void writeSpawn(sf::Packet& packet);
	virtual void readSpawn(sf::Packet& packet);
private:
	bool isRemote;
	int clientId;
};

