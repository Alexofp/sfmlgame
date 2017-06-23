#include "ItemManager.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

void ItemManager::loadItems(std::string path)
{
	std::ifstream file(path);
	json jsonData;
	file >> jsonData;

	for (auto& item : jsonData)
	{
		std::string name = item["name"].get<std::string>();
		std::string textName = item["textName"].get<std::string>();
		std::string description = item["description"].get<std::string>();
		std::string texture = item["texture"].get<std::string>();
		int w = item["w"].get<int>()-1;
		int h = item["h"].get<int>()-1;

		Item item;
		item.name = name;
		item.textName = textName;
		item.description = description;
		item.texture = texture;
		item.w = w;
		item.h = h;

		getInstance().items[name] = item;
	}
}

ItemManager::Item ItemManager::getItem(std::string name)
{
	return getInstance().items.at(name);
}

ItemManager & ItemManager::getInstance()
{
	static ItemManager manager;
	return manager;
}
