#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
#include "Inventory.h"
#include "Vec2f.h"
#include <vector>

class InventoryPanel
{
public:
	InventoryPanel();
	~InventoryPanel();

	void setInventory(Inventory* inv);
	void updatePanel();
	void setPos(Vec2f pos);
	Vec2f getSize();

	int getAt(Vec2f pos);
	Inventory::Item* getItem(int index);
	void selectItem(Vec2i pos, Vec2i size);
	void clearSelection();
	bool removeItem(int index);
	bool addItem(Inventory::ItemInfo info);

	void draw();

	Vec2f actualSize;
private:
	bool dirty;
	sf::RectangleShape background;
	sf::RectangleShape selection;
	std::vector<sf::RectangleShape> cells;
	Inventory* inventory;
	float cellSize;
	Vec2f size;
	Vec2f pos;

};

