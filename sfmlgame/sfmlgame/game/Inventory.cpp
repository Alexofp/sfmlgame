#include "Inventory.h"



Inventory::Inventory()
{
	w = 5;
	h = 5;
}

Inventory::Inventory(int w, int h)
{
	this->w = w;
	this->h = h;
}


Inventory::~Inventory()
{
}

bool Inventory::placeFree(Vec2i pos, Vec2i size)
{
	Vec2i leftTop = pos;
	Vec2i rightBottom(pos.x + size.x, pos.y + size.y);

	if (leftTop.x < 0 || leftTop.y < 0)
		return false;
	if (rightBottom.x >= w || rightBottom.y >= h)
	{
		return false;
	}

	for (auto& item : items)
	{
		Vec2i lt = item.pos;
		Vec2i rb(item.pos.x + item.size.x, item.pos.y + item.size.y);

		if (rightBottom.x >= lt.x && rb.x >= leftTop.x &&
			rightBottom.y >= lt.y && rb.y >= leftTop.y)
		{
			return false;
		}
	}
	return true;
}

bool Inventory::addItem(Item item)
{
	ItemManager::Item info = ItemManager::getItem(item.name);
	item.size = Vec2i(info.w, info.h);

	if (placeFree(item.pos, item.size))
	{
		items.push_back(item);
		return true;
	}

	return false;
}

bool Inventory::addItemAnywhere(Item item)
{
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (placeFree(Vec2i(x, y), item.size))
			{
				item.pos = Vec2i(x, y);
				items.push_back(item);
				return true;
			}
		}
	}

	return false;
}

Vec2i Inventory::getSize()
{
	return Vec2i(w,h);
}

void Inventory::setSize(Vec2i size)
{
	w = size.x;
	h = size.y;
}

std::vector<Inventory::Item>& Inventory::getItems()
{
	return items;
}
