#pragma once
#include "Entity.h"
#include "SimpleSprite.h"
#include "AnimatedSkeleton.h"
#include "Skin.h"
#include "Animation.h"

class Player: public Entity
{
public:
	Player(int nid = -1);
	~Player();

	void update(float dt);
	void localUpdate(float dt);
	void draw();
	void setRemote(bool isRemote);

	virtual void writeInformation(sf::Packet& packet);
	virtual void readInformation(sf::Packet& packet);
private:
	SimpleSprite sprite;
	AnimatedSkeleton skeleton;
	Animation walkAnim;
	Animation hitAnim;
	Vec2f speed;
	bool isRemote;
	bool attacking;
};

