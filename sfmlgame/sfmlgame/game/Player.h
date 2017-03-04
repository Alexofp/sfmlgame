#pragma once
#include "Entity.h"
#include "SimpleSprite.h"
#include "AnimatedSkeleton.h"
#include "Skin.h"
#include "Animation.h"
#include "PhysicsEntity.h"

class Player: public PhysicsEntity
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
	SimpleSprite sprite;
	AnimatedSkeleton skeleton;
	Animation walkAnim;
	Animation hitAnim;
	Vec2f speed;
	bool isRemote;
	bool attacking;
	int clientId;
};

