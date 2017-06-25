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

	for (auto& itemJson : jsonData)
	{
		std::string name = itemJson["name"].get<std::string>();
		std::string textName = itemJson["textName"].get<std::string>();
		std::string description = itemJson["description"].get<std::string>();
		std::string texture = itemJson["texture"].get<std::string>();
		int w = itemJson["w"].get<int>()-1;
		int h = itemJson["h"].get<int>()-1;
		std::string type = itemJson["type"].get<std::string>();

		Item item;
		item.name = name;
		item.textName = textName;
		item.description = description;
		item.texture = texture;
		item.w = w;
		item.h = h;
		item.type = type;
		if (type == "weapon")
		{
			item.weaponType = itemJson["weaponType"].get<std::string>();
		}

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
