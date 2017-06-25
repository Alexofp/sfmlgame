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
	bulletsClearDestroyed();
}

void GameWorld::localUpdate(float dt)
{
	for (auto& entity : entities)
	{
		entity->localUpdate(dt);
	}
	bulletsClearDestroyed();
}

void GameWorld::physicsUpdate(float dt)
{
	physics.update(dt);
	for (auto& entity : bullets)
	{
		entity->update(dt);
	}
	bulletsClearDestroyed();
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
	for (auto& entity : bullets)
	{
		entity->draw();
	}
}

void GameWorld::loadMap(std::string name)
{
	terrain.load("maps/"+ name +"/");
	objects.loadFromFile("maps/" + name + "/objects.json");
}

Bullet * GameWorld::fireBullet(Vec2f pos, Vec2f speed)
{
	PhysicsBody* bulletBody = physics.createBullet(pos, 10.f);
	Bullet* bullet = new Bullet(bulletBody);
	bullet->setPos(pos);
	bullet->setSpeed(speed);
	bullets.push_back(std::unique_ptr<Bullet>(bullet));
	return bullet;
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

void GameWorld::bulletsClearDestroyed()
{
	auto new_end = std::remove_if(bullets.begin(), bullets.end(),
		[](std::unique_ptr<Bullet>& bullet)
	{
		return bullet->isDestroyed();
	});

	bullets.erase(new_end, bullets.end());
}
