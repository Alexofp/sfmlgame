#pragma once
#include <Box2D\Box2D.h>
#include <vector>
#include <memory>
#include "Vec2f.h"
#include "ContactListener.h"
#include "PhysicsEntity.h"

enum class PhysicsEntityCategory {
	STATIC = 0x0001,
	ENTITY = 0x0002,
	BULLET = 0x0004
};

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

	void setLinearDamping(float a);
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
	void setTag(void* tag);
	void* getTag();
	void destroy();
	b2Body* getInternalBody();
	bool isDestroyed();
	void setEntity(PhysicsEntity* entity);
	PhysicsEntity* getEntity();
private:
	void* tag;
	b2Body* body;
	PhysicsWorld* world;
	PhysicsEntity* entity;
	Type type;
	Vec2f size;
	bool destroyed;
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
	PhysicsBody* createBullet(Vec2f pos, float radius);

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
	ContactListener listener;
};

