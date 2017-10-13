#pragma once
#include "PhysicsEntity.h"
#include "SimpleSprite.h"
#include "AnimatedSkeleton.h"
#include "Skin.h"
#include "Animation.h"
#include "HealthBar.h"

class AliveEntity :	public PhysicsEntity
{
public:
	AliveEntity(int nid = -1);
	virtual ~AliveEntity();

	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void localUpdate(float dt) = 0;
	virtual void draw() = 0;
	void updateMove(float dt);
	void setTarget(Vec2f target);

	virtual void handleEvent(int fromId, std::string type, sf::Packet& packet);
	virtual void onDeath();
	void drawHealthBar();

	int getHealth();
	int getMaxHealth();
protected:
	Vec2f speed;
	float maxSpeed;
	float acceleration;

	Vec2f targetSpeed;
	int health;
	int maxHealth;

	HealthBar healthBar;
};

