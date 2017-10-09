#include "Entity.h"
#include "Server.h"
#include "Log.h"
#include "Client.h"
#include "GameWorld.h"

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

void Entity::writeInformation(sf::Packet & packet)
{
	packet << pos.x << pos.y << size.x << size.y << angle;
}

void Entity::readInformation(sf::Packet & packet)
{
	packet >> pos.x >> pos.y >> size.x >> size.y >> angle;
}

void Entity::writeSpawn(sf::Packet & packet)
{
	packet << pos.x << pos.y << size.x << size.y << angle;
}

void Entity::readSpawn(sf::Packet & packet)
{
	packet >> pos.x >> pos.y >> size.x >> size.y >> angle;
}

void Entity::sendEvent(NetEvent event)
{
	if (Server::isInServer())
	{
		Server::send(event);

		Entity* ent = world->findEntity(event.toId);
		if (ent != 0)
		{
			ent->handleEvent(event.fromId, event.type, event.data);
		}
		else
		{
			Log::debug("wtf");
		}
	}
	else
	{
		Client::send(event);
	}
}

void Entity::handleEvent(int fromId, std::string type, sf::Packet & packet)
{
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
