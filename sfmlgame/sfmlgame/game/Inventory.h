#pragma once
#include "Vec2i.h"
#include <vector>
#include "ItemManager.h"

class Inventory
{
public:
	struct Item
	{
		Item(Vec2i pos, std::string name)
		{
			this->pos = pos;
			this->name = name;
		}

		Vec2i pos;
		Vec2i size;
		std::string name;
	};

	Inventory();
	Inventory(int w, int h);
	~Inventory();

	bool placeFree(Vec2i pos, Vec2i size);
	bool addItem(Item item);
	bool addItemAnywhere(Item item);

	Vec2i getSize();
	void setSize(Vec2i size);
	std::vector<Item>& getItems();

private:
	int w;
	int h;

	std::vector<Item> items;
};

