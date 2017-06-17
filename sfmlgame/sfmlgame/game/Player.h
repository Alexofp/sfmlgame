#pragma once
#include "Entity.h"
#include "SimpleSprite.h"
#include "AnimatedSkeleton.h"
#include "Skin.h"
#include "Animation.h"
#include "PhysicsEntity.h"
#include "AliveEntity.h"

class Player: public AliveEntity
{
public:
	Player(int clientId, int nid = -1);
	~Player();

	void init();
	void update(float dt);
	void localUpdate(float dt);
	void draw();
	void setRemote(bool isRemote);

	int getClientId();

	virtual MultiplayerMessage writeInformation();
	virtual void readInformation(MultiplayerMessage& message);
	MultiplayerMessage spawnMessage();
private:
	Animation walkAnim;
	Animation hitAnim;
	bool isRemote;
	bool attacking;
	int clientId;
};

