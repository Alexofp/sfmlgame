#include "Entity.h"



Entity::Entity()
{
	pos = Vec2f();
	size = Vec2f();
	angle = 0.f;
}


Entity::~Entity()
{
}

void Entity::setPos(Vec2f pos)
{
	this->pos = pos;
}

void Entity::setSize(Vec2f size)
{
	this->size = size;
}

void Entity::setAng(float ang)
{
	this->angle = ang;
}

Vec2f Entity::getPos()
{
	return pos;
}

Vec2f Entity::getSize()
{
	return size;
}

float Entity::getAng()
{
	return angle;
}
