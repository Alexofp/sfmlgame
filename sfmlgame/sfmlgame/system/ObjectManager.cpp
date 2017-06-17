#include "ObjectManager.h"
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::loadFromFile(std::string path)
{
	std::ifstream input(path);

	std::string file;
	while (input >> file)
	{
		if (file != "")
		{
			loadObject(file);
		}
	}
}

void ObjectManager::loadObject(std::string path)
{
	std::ifstream file(path);
	json jsonData;
	file >> jsonData;

	StaticObject object;

	std::string name = jsonData["name"].get<std::string>();
	object.setName(name);
	Vec2f shadowPos(jsonData["shadow"][0].get<float>(), jsonData["shadow"][1].get<float>());
	object.setShadowPos(shadowPos);

	for (json::iterator it = jsonData["parts"].begin(); it != jsonData["parts"].end(); ++it)
	{
		auto part = it.value();
		std::string texture = part["texture"].get<std::string>();
		float xpos, ypos;
		xpos = part["pos"][0].get<float>();
		ypos = part["pos"][1].get<float>();
		float w, h;
		w = part["size"][0].get<float>();
		h = part["size"][1].get<float>();
		float angle;
		angle = part["angle"].get<float>();

		StaticObject::Part staticpart;
		staticpart.pos = Vec2f(xpos,ypos);
		staticpart.ang = angle;
		staticpart.size = Vec2f(w, h);
		staticpart.texture = texture;

		object.addPart(staticpart);
	}

	for (json::iterator it = jsonData["collisions"].begin(); it != jsonData["collisions"].end(); ++it)
	{
		auto part = it.value();
		std::string type = part["type"].get<std::string>();

		StaticObject::CollisionPart collpart;
		collpart.pos.x = part["pos"][0].get<float>();
		collpart.pos.y = part["pos"][1].get<float>();
		if (type == "circle")
		{
			StaticObject::CircleCollision circle;
			circle.radius = part["size"].get<float>();
			collpart.circle = circle;
			collpart.type = StaticObject::CollisionType::CIRCLE;
		}
		if (type == "box")
		{
			StaticObject::BoxCollision box;
			box.size.x = part["size"][0].get<float>();
			box.size.y = part["size"][1].get<float>();
			box.angle = part["angle"].get<float>();
			collpart.box = box;
			collpart.type = StaticObject::CollisionType::BOX;
		}

		object.addCollisionPart(collpart);
	}

	getInstance().objects[name] = object;
}

StaticObject ObjectManager::getObject(std::string name)
{
	return getInstance().objects.at(name);
}

std::vector<std::string> ObjectManager::getObjectNames()
{
	std::vector<std::string> result;
	for (auto& pair : getInstance().objects)
	{
		result.push_back(pair.first);
	}
	return result;
}

ObjectManager & ObjectManager::getInstance()
{
	static ObjectManager manager;
	return manager;
}
