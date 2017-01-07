#pragma once
#include "Entity.h"
#include "SimpleSprite.h"

class Player: public Entity
{
public:
	Player();
	~Player();

	void update(float dt);
	void draw();
private:
	SimpleSprite sprite;
	Vec2f speed;
};

