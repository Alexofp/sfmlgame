#include "ObjectHandler.h"
#include "GameWindow.h"
#include "GameWorld.h"

ObjectHandler::ObjectHandler()
{
	world = 0;
}

ObjectHandler::ObjectHandler(GameWorld * world)
{
	this->world = world;
}


ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::addObject(StaticObject object)
{
	objects.push_back(object);

	if (world)
	{
		objects.back().init(world);
	}
}

void ObjectHandler::draw()
{
	for (auto& object : objects)
	{
		object.draw();
	}
}
