#pragma once
#include "Entity.h"
#include <vector>
#include <memory>
#include "PhysicsWorld.h"
#include "ObjectHandler.h"
#include "ObjectManager.h"
#include "Terrain.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void update(float dt);
	void localUpdate(float dt);
	void physicsUpdate(float dt);
	void draw();
	void loadMap(std::string name);

	void add(Entity* entity);
	Entity* findEntity(int nid);
	PhysicsWorld& getPhysicsWorld();
	std::vector<std::unique_ptr<Entity> >& getEntities();
	void addObject(std::string type, Vec2f pos, float angle = 0.f, Vec2f size = Vec2f(1.f,1.f));
	std::vector<Entity*> findInRange(Vec2f pos, float radius);

private:
	std::vector<std::unique_ptr<Entity> > entities;
	PhysicsWorld physics;
	ObjectHandler objects;
	Terrain terrain;
};

