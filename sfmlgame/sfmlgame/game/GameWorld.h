#pragma once
#include "Entity.h"
#include <vector>
#include <memory>
#include "PhysicsWorld.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void update(float dt);
	void localUpdate(float dt);
	void physicsUpdate(float dt);
	void draw();

	void add(Entity* entity);
	Entity* findEntity(int nid);
	PhysicsWorld& getPhysicsWorld();
	std::vector<std::unique_ptr<Entity> >& getEntities();

private:
	std::vector<std::unique_ptr<Entity> > entities;
	PhysicsWorld physics;
};

