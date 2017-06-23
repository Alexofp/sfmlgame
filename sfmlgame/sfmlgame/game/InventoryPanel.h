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

	Inventory::Item* getAt(Vec2f pos);
	void selectItem(Vec2i pos, Vec2i size);
	void clearSelection();

	void draw();

	Vec2f actualSize;
private:
	sf::RectangleShape background;
	sf::RectangleShape selection;
	std::vector<sf::RectangleShape> cells;
	Inventory* inventory;
	float cellSize;
	Vec2f size;
	Vec2f pos;

};

