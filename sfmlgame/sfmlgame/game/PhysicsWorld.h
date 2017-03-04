#pragma once
#include <Box2D\Box2D.h>
#include <vector>
#include <memory>
#include "Vec2f.h"

class PhysicsWorld;

class PhysicsBody
{
public:
	PhysicsBody(PhysicsWorld* world, b2Body* body);
	~PhysicsBody();

	Vec2f getPos();
	void setPos(Vec2f pos);
	float getAng();
	void setAng(float ang);
	Vec2f getSpeed();
	void setSpeed(Vec2f speed);
private:
	b2Body* body;
	PhysicsWorld* world;
};

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	PhysicsBody* createCircle(Vec2f pos, float radius);

	float worldToB2World;
	b2Vec2 translate(Vec2f p);
	Vec2f translate(b2Vec2 p);
	void destroy(PhysicsBody* body);
	void update(float dt);
private:


	b2World world;
	std::vector<std::unique_ptr<PhysicsBody> > bodies;
	std::vector<PhysicsBody*> toDestroy;
	float time;
	float timestep;
};

