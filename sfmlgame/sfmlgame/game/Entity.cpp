#include "Entity.h"
#include "Server.h"
#include "Log.h"

Entity::Entity(int nid)
{
	pos = Vec2f();
	size = Vec2f();
	angle = 0.f;
	realType = Type::Entity;

	if (nid < 0)
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

MultiplayerMessage Entity::writeInformation()
{
	MultiplayerMessage message(MessageType::NoMessage);
	return message;
}

void Entity::readInformation(MultiplayerMessage& message)
{
	//packet >> pos.x >> pos.y >> size.x >> size.y >> angle;
}

MultiplayerMessage Entity::spawnMessage()
{
	return MultiplayerMessage(MessageType::NoMessage);
}

int Entity::getNid()
{
	return nid;
}

Entity::Type Entity::getType()
{
	return realType;
}

void Entity::add(GameWorld * world)
{
	this->world = world;
	init();
}
