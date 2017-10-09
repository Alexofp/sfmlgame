#include "PhysicsEntity.h"
#include "GameWorld.h"

PhysicsEntity::PhysicsEntity(int nid):
	Entity(nid)
{
}

PhysicsEntity::~PhysicsEntity()
{
}

void PhysicsEntity::setBodyPos(Vec2f pos)
{
	body->setPos(pos);
}

void PhysicsEntity::setBodyAng(float ang)
{
	body->setAng(ang);
}

void PhysicsEntity::setBodySpeed(Vec2f speed)
{
	body->setSpeed(speed);
}

Inventory & PhysicsEntity::getInventory()
{
	return inventory;
}

Vec2f PhysicsEntity::getBodyPos()
{
	return body->getPos();
}

float PhysicsEntity::getBodyAng()
{
	return body->getAng();
}

Vec2f PhysicsEntity::getBodySpeed()
{
	return body->getSpeed();
}

void PhysicsEntity::updateBody()
{
	setPos(getBodyPos());
	setAng(getBodyAng());
}
