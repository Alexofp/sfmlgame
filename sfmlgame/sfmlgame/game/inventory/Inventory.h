#pragma once
#include "Vec2i.h"
#include <vector>
#include "ItemManager.h"

class Inventory
{
public:
	struct AmmoInfo
	{
		int count;
	};

	struct ItemInfo
	{
		std::string name;
		ItemManager::Item getInfo()
		{
			return ItemManager::getItem(name);
		}

		union
		{
			AmmoInfo ammo;
		};
	};

	struct Item
	{
		Item(Vec2i pos, std::string name)
		{
			this->pos = pos;
			this->info.name = name;
		}
		Item(Vec2i pos, ItemInfo info)
		{
			this->pos = pos;
			this->info = info;
		}

		Vec2i pos;
		Vec2i size;
		ItemInfo info;
	};

	Inventory();
	Inventory(int w, int h);
	~Inventory();

	bool placeFree(Vec2i pos, Vec2i size);
	bool addItem(Item item);
	bool addItemAnywhere(Item item);
	bool addItem(ItemInfo item);
	Item* getItem(int index);
	bool removeItem(int index);
	void clear();

	Vec2i getSize();
	void setSize(Vec2i size);
	std::vector<Item>& getItems();
	int getAmmoCount(std::string ammoType);
	int removeAmmo(std::string ammoType, int ammount);

private:
	int w;
	int h;

	std::vector<Item> items;
};

