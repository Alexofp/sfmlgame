#include "GameWorld.h"



GameWorld::GameWorld():
	objects(this)
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
	terrain.draw();
	objects.drawShadow();
	objects.draw();
	for (auto& entity : entities)
	{
		entity->draw();
	}
}

void GameWorld::loadMap(std::string name)
{
	terrain.load("maps/"+ name +"/");
	objects.loadFromFile("maps/" + name + "/objects.json");
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

void GameWorld::addObject(std::string type, Vec2f pos, float angle, Vec2f size)
{
	StaticObject object = ObjectManager::getObject(type);
	object.setPos(pos);
	object.setSize(size);
	object.setAng(angle);
	objects.addObject(object);
}

std::vector<Entity*> GameWorld::findInRange(Vec2f pos, float radius)
{
	std::vector<Entity*> result;
	for (auto& entity : entities)
	{
		float dist = Vec2f::distance(entity->getPos(), pos);

		if (dist <= radius)
		{
			result.push_back(entity.get());
		}
	}

	return result;
}
