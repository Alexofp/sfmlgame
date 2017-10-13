#include "InventoryPanel.h"
#include "GameWindow.h"
#include "TextureManager.h"
#include "Util.h"
#include "gui.h"

InventoryPanel::InventoryPanel()
{
	inventory = 0;
	cellSize = 50.f;
	pos = Vec2f();

	selection.setFillColor(sf::Color::Transparent);
	selection.setOutlineColor(sf::Color::Red);
	selection.setOutlineThickness(2.f);

	actualSize = Vec2f(800.f, 800.f);
	dirty = true;
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
		size = panelSize;

		background.setSize(panelSize.toSFMLVec());

		cells.clear();
		invcells.clear();
		for (int x = 0; x < invSize.x; x++)
		{
			for (int y = 0; y < invSize.y; y++)
			{
				float padding = 10.f;

				sf::RectangleShape cell;
				//cell.setFillColor(sf::Color::Transparent);
				//cell.setOutlineColor(sf::Color::Red);
				//cell.setOutlineThickness(2.f);
				cell.setFillColor(sf::Color(0, 0, 0, 100));
				cell.setPosition(sf::Vector2f(x*cellSize, y*cellSize));
				cell.setSize(sf::Vector2f(cellSize - padding, cellSize - padding));
				cell.setOrigin(-padding / 2.f, -padding / 2.f);
				invcells.push_back(cell);
			}
		}

		for (auto& item : inventory->getItems())
		{
			Cell cell;
			cell.fill(item, cellSize);
			cells.push_back(cell);
		}
	}
}

void InventoryPanel::setPos(Vec2f pos)
{
	this->pos = pos;
}

Vec2f InventoryPanel::getSize()
{
	return size;
}

int InventoryPanel::getAt(Vec2f pos)
{
	if (inventory == 0)
		return -1;

	sf::Transform transform;

	transform.translate(this->pos.toSFMLVec());
	transform.scale(actualSize.x / size.x, actualSize.y / size.y);

	pos = transform.getInverse().transformPoint(pos.toSFMLVec());

	int i = 0;
	for (auto& item : inventory->getItems())
	{
		Vec2f cellPos(item.pos.x*cellSize, item.pos.y*cellSize);
		Vec2f cellSize((item.size.x + 1)*cellSize, (item.size.y + 1)*cellSize);

		if(Util::boxCollision2(cellPos, cellSize, pos, Vec2f(1.f, 1.f)))
		{
			return i;
			//return &item;
		}
		i++;
	}

	return -1;
}

Inventory::Item * InventoryPanel::getItem(int index)
{
	return inventory->getItem(index);
}

void InventoryPanel::selectItem(Vec2i pos, Vec2i size)
{
	Vec2f cellPos(pos.x*cellSize, pos.y*cellSize);
	Vec2f cellSize((size.x + 1)*cellSize, (size.y + 1)*cellSize);

	selection.setPosition(cellPos.toSFMLVec());
	selection.setSize(cellSize.toSFMLVec());
}

void InventoryPanel::clearSelection()
{
	selection.setSize(sf::Vector2f(0.f,0.f));
}

bool InventoryPanel::removeItem(int index)
{
	if (inventory->removeItem(index))
	{
		dirty = true;
		return true;
	}
	return false;
}

bool InventoryPanel::addItem(Inventory::ItemInfo info)
{
	return inventory->addItem(info);
}

void InventoryPanel::draw()
{
	if (dirty)
	{
		dirty = false;
		updatePanel();
	}

	sf::RenderStates states;

	sf::Transform transform;
	
	transform.translate(pos.toSFMLVec());
	transform.scale(actualSize.x / size.x, actualSize.y / size.y);

	states.transform = transform;

	GameWindow::getInternalHandle().draw(background, states);

	for (auto& cell : invcells)
	{
		GameWindow::getInternalHandle().draw(cell, states);
	}
	for (auto& cell : cells)
	{
		cell.draw(states);
	}

	GameWindow::getInternalHandle().draw(selection, states);
}

void InventoryPanel::Cell::fill(Inventory::Item & item, float cellSize)
{
	type = 0;
	ItemManager::Item info = ItemManager::getItem(item.info.name);
	if (info.type == "ammo")
	{
		type = 1;
	}

	Vec2f cellPos(item.pos.x*cellSize, item.pos.y*cellSize);
	Vec2f cellSizeVec((item.size.x + 1)*cellSize, (item.size.y + 1)*cellSize);

	shape.setTexture(TextureManager::get(info.texture));
	shape.setPosition(cellPos.toSFMLVec());
	shape.setSize(cellSizeVec.toSFMLVec());

	if (type == 1)
	{
		text.setFont(Gui::getDefaultFont());
		text.setString(std::to_string(item.info.ammo.count));
		text.setCharacterSize(18u);
		text.setPosition(cellPos.toSFMLVec()+sf::Vector2f(1.f,1.f));
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(1.0f);
	}
}

void InventoryPanel::Cell::draw(sf::RenderStates& states)
{
	GameWindow::getInternalHandle().draw(shape, states);

	if (type == 1)
	{
		GameWindow::getInternalHandle().draw(text, states);
	}
}
