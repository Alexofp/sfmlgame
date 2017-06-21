#pragma once
#include "Vec2i.h"
#include <vector>

class Inventory
{
public:
	struct Item
	{
		Vec2i pos;
		Vec2i size;
	};

	Inventory(int w, int h);
	~Inventory();

	bool placeFree(Vec2i pos, Vec2i size);
	bool addItem(Item item);
	bool addItemAnywhere(Item item);

	Vec2i getSize();
	std::vector<Item>& getItems();

private:
	int w;
	int h;

	std::vector<Item> items;
};

