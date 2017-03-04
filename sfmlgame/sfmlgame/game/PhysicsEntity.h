#pragma once
#include "Entity.h"

class PhysicsBody;

class PhysicsEntity :
	public Entity
{
public:
	PhysicsEntity(int nid = -1);
	~PhysicsEntity();

	void setBodyPos(Vec2f pos);
	void setBodyAng(float ang);
	void setBodySpeed(Vec2f speed);

	Vec2f getBodyPos();
	float getBodyAng();
	Vec2f getBodySpeed();

	void updateBody();

protected:
	PhysicsBody* body;
};

