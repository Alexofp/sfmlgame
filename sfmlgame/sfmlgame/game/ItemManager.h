#pragma once
#include <string>
#include <unordered_map>

class ItemManager
{
public:
	struct Item
	{
		std::string name;
		std::string textName;
		std::string description;
		std::string texture;
		int w;
		int h;
	};

	ItemManager();
	~ItemManager();

	static void loadItems(std::string path);
	static Item getItem(std::string name);

private:
	static ItemManager& getInstance();

	std::unordered_map<std::string, Item> items;
};

