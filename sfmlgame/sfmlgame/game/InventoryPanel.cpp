#include "InventoryPanel.h"
#include "GameWindow.h"


InventoryPanel::InventoryPanel()
{
	inventory = 0;
	cellSize = 50.f;
}


InventoryPanel::~InventoryPanel()
{
}

void InventoryPanel::setInventory(Inventory * inv)
{
	inventory = inv;

	updatePanel();
}

void InventoryPanel::updatePanel()
{
	if (inventory != 0)
	{
		Vec2i invSize = inventory->getSize();

		Vec2f panelSize(invSize.x*cellSize, invSize.y*cellSize);

		background.setSize(panelSize.toSFMLVec());

		cells.clear();
		for (int x = 0; x < invSize.x; x++)
		{
			for (int y = 0; y < invSize.y; y++)
			{
				float padding = 10.f;

				sf::RectangleShape cell;
				cell.setFillColor(sf::Color::Transparent);
				cell.setOutlineColor(sf::Color::Red);
				cell.setOutlineThickness(2.f);
				cell.setPosition(sf::Vector2f(x*cellSize, y*cellSize));
				cell.setSize(sf::Vector2f(cellSize - padding, cellSize - padding));
				cell.setOrigin(-padding / 2.f, -padding / 2.f);
				cells.push_back(cell);
			}
		}

		for (auto& item : inventory->getItems())
		{
			Vec2f cellPos(item.pos.x*cellSize, item.pos.y*cellSize);
			Vec2f cellSize((item.size.x+1)*cellSize, (item.size.y+1)*cellSize);

			sf::RectangleShape cell;
			cell.setFillColor(sf::Color(0,0,255,100));
			cell.setOutlineColor(sf::Color::Red);
			cell.setOutlineThickness(2.f);
			cell.setPosition(cellPos.toSFMLVec());
			cell.setSize(cellSize.toSFMLVec());
			cells.push_back(cell);
		}
	}
}

void InventoryPanel::draw()
{
	GameWindow::getInternalHandle().draw(background);

	for (auto& cell : cells)
	{
		GameWindow::getInternalHandle().draw(cell);
	}
}
