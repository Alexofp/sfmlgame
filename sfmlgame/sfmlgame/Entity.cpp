#include "Entity.h"
#include "Server.h"
#include "Log.h"

Entity::Entity(int nid)
{
	pos = Vec2f();
	size = Vec2f();
	angle = 0.f;
	realType = Type::Entity;
	type = SyncType::Entity;

	if (Server::isServer())
	{
		this->nid = Server::getNewEntityId();
	}
	else
	{
		this->nid = nid;
	}
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

void Entity::writeInformation(sf::Packet & packet)
{
	packet << pos.x << pos.y << size.x << size.y << angle;
}

void Entity::readInformation(sf::Packet & packet)
{
	packet >> pos.x >> pos.y >> size.x >> size.y >> angle;
}

int Entity::getNid()
{
	return nid;
}

Entity::SyncType Entity::getSyncType()
{
	return type;
}

Entity::Type Entity::getType()
{
	return realType;
}
