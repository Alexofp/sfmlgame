#pragma once
#include <Box2D\Box2D.h>
#include <vector>
#include <memory>
#include "Vec2f.h"

class PhysicsWorld;

class PhysicsBody
{
public:
	enum class Type
	{
		Circle,
		Box
	};

	PhysicsBody(PhysicsWorld* world, b2Body* body, Type type);
	~PhysicsBody();

	Vec2f getPos();
	void setPos(Vec2f pos);
	float getAng();
	void setAng(float ang);
	Vec2f getSpeed();
	void setSpeed(Vec2f speed);
	float getRadius();
	Type getType();
	void setSize(Vec2f size);
	Vec2f getSize();
	std::vector<std::vector<Vec2f> > getPoints();
private:
	b2Body* body;
	PhysicsWorld* world;
	Type type;
	Vec2f size;
};

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	PhysicsBody* createCircle(Vec2f pos, float radius);
	PhysicsBody* createStaticCircle(Vec2f pos, float radius);
	PhysicsBody* createStaticBox(Vec2f pos, Vec2f size);
	PhysicsBody* createBox(Vec2f pos, Vec2f size);

	float worldToB2World;
	b2Vec2 translate(Vec2f p);
	Vec2f translate(b2Vec2 p);
	void destroy(PhysicsBody* body);
	void update(float dt);
	void debugDraw();
private:


	b2World world;
	std::vector<std::unique_ptr<PhysicsBody> > bodies;
	std::vector<PhysicsBody*> toDestroy;
	float time;
	float timestep;
};

