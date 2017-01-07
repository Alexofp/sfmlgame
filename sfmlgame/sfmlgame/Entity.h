#pragma once
#include "Vec2f.h"

class Entity
{
public:
	Entity();
	~Entity();

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	void setPos(Vec2f pos);
	void setSize(Vec2f size);
	void setAng(float ang);

	Vec2f getPos();
	Vec2f getSize();
	float getAng();
private:
	Vec2f pos;
	Vec2f size;
	float angle;
};

