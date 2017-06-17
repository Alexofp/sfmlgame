#include "ObjectHandler.h"
#include "GameWindow.h"
#include "GameWorld.h"
#include "json.hpp"
#include <fstream>
#include "util.h"
using json = nlohmann::json;

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

void ObjectHandler::drawShadow()
{
	for (auto& object : objects)
	{
		object.drawShadow();
	}
}

void ObjectHandler::saveToFile(std::string path)
{
	json jsonData;

	for (auto& object : objects)
	{
		json jsonObject;
		jsonObject["type"] = object.getName();
		jsonObject["pos"][0] = object.getPos().x;
		jsonObject["pos"][1] = object.getPos().y;
		jsonObject["size"][0] = object.getSize().x;
		jsonObject["size"][1] = object.getSize().y;
		jsonObject["angle"] = object.getAng();

		jsonData["objects"].push_back(jsonObject);
	}

	std::ofstream o(path);
	o << std::setw(4) << jsonData << std::endl;
}

void ObjectHandler::loadFromFile(std::string path)
{
	clear();

	if (!Util::fileExists(path))
		return;
	std::ifstream file(path);
	json jsonData;
	file >> jsonData;

	for (auto& jsonObject : jsonData["objects"])
	{
		std::string type = jsonObject["type"].get<std::string>();
		Vec2f pos(jsonObject["pos"][0].get<float>(), jsonObject["pos"][1].get<float>());
		Vec2f size(jsonObject["size"][0].get<float>(), jsonObject["size"][1].get<float>());
		float angle = jsonObject["angle"].get<float>();

		StaticObject object = ObjectManager::getObject(type);
		object.setPos(pos);
		object.setSize(size);
		object.setAng(angle);
		addObject(object);
	}
}

void ObjectHandler::remoteObjectAt(Vec2f pos, float radius)
{
	int closestObject = -1;
	float minDist = radius;

	int i = 0;
	for (auto& object : objects)
	{
		float dist = Vec2f::distance(object.getPos(), pos);
		if (dist < minDist)
		{
			minDist = dist;
			closestObject = i;
		}
		i++;
	}

	if (closestObject >= 0)
	{
		objects.erase(objects.begin() + closestObject);
	}
}

void ObjectHandler::clear()
{
	objects.clear();
}
