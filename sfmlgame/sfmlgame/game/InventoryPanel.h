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

	void draw();
private:
	sf::RectangleShape background;
	std::vector<sf::RectangleShape> cells;
	Inventory* inventory;
	float cellSize;
	Vec2f size;
};

