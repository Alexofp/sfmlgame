#pragma once
#include "StaticObject.h"
#include <unordered_map>
#include <string>
#include <memory>


class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	static void loadFromFile(std::string path);
	static void loadObject(std::string path);
	static StaticObject getObject(std::string name);

private:
	static ObjectManager& getInstance();

	std::unordered_map<std::string, StaticObject> objects;
};

