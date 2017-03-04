#include "GameWorld.h"



GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::update(float dt)
{
	for (auto& entity : entities)
	{
		entity->update(dt);
	}
}

void GameWorld::localUpdate(float dt)
{
	for (auto& entity : entities)
	{
		entity->localUpdate(dt);
	}
}

void GameWorld::physicsUpdate(float dt)
{
	physics.update(dt);
}

void GameWorld::draw()
{
	for (auto& entity : entities)
	{
		entity->draw();
	}
}

void GameWorld::add(Entity * entity)
{
	entity->add(this);
	entities.push_back(std::unique_ptr<Entity>(entity));
}

Entity * GameWorld::findEntity(int nid)
{
	for (auto& entity : entities)
	{
		if (entity->getNid() == nid)
			return entity.get();
	}

	return nullptr;
}

PhysicsWorld & GameWorld::getPhysicsWorld()
{
	return physics;
}

std::vector<std::unique_ptr<Entity>>& GameWorld::getEntities()
{
	return entities;
}
