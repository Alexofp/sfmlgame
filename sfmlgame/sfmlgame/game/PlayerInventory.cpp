#include "PlayerInventory.h"
#include "GameWindow.h"
#include "Util.h"
#include <iostream>

PlayerInventory::PlayerInventory()
{
	player = 0;
	background.setFillColor(sf::Color(200, 200, 200));

	name.setFont(Gui::getDefaultFont());
	description.setFont(Gui::getDefaultFont());
	name.setCharacterSize(40u);
	description.setCharacterSize(32u);
	name.setFillColor(sf::Color::Black);
	description.setFillColor(sf::Color::Black);

	show = false;
}


PlayerInventory::~PlayerInventory()
{
}

void PlayerInventory::setPlayer(Player * player)
{
	this->player = player;
	panel.setInventory(&player->getInventory());
	resize();
}

void PlayerInventory::draw()
{
	if (!show)
		return;

	sf::View oldView = GameWindow::getInternalHandle().getView();
	GameWindow::getInternalHandle().setView(guiView);
	GameWindow::getInternalHandle().draw(background);
	panel.draw();

	GameWindow::getInternalHandle().draw(name);
	GameWindow::getInternalHandle().draw(description);
	GameWindow::getInternalHandle().setView(oldView);
}

void PlayerInventory::resize()
{
	Vec2f size = Vec2f(GameWindow::getSize().x, GameWindow::getSize().y);

	Vec2f panelSize = panel.actualSize;

	Vec2f backgroundSize = Vec2f(panelSize.x+800.f, panelSize.y+80.f);
	background.setSize(backgroundSize.toSFMLVec());

	Vec2f viewSize = Util::fitView(size, backgroundSize, 10.f);

	guiView.setSize(viewSize.toSFMLVec());
	guiView.setCenter(sf::Vector2f(viewSize.x / 2.f, viewSize.y / 2.f));

	Vec2f centerPanel = Vec2f::sub(Vec2f::mul(viewSize,0.5f), Vec2f::mul(backgroundSize, 0.5f));

	panel.setPos(centerPanel);
	background.setPosition(centerPanel.toSFMLVec());

	name.setPosition(centerPanel.toSFMLVec()+sf::Vector2f(810.f,10.f));
	description.setPosition(centerPanel.toSFMLVec() + sf::Vector2f(810.f, 80.f));
}

void PlayerInventory::toggle()
{
	show = !show;
}

bool PlayerInventory::handleEvent(sf::Event event)
{
	if (!show)
		return false;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			Vec2f mousePos = GameWindow::getInternalHandle().mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), guiView);

			Inventory::Item* selectedItem = panel.getAt(mousePos);

			if (selectedItem != 0)
			{
				panel.selectItem(selectedItem->pos, selectedItem->size);

				ItemManager::Item item = ItemManager::getItem(selectedItem->name);
				name.setString(item.textName);
				description.setString(item.description);
			}
			else
			{
				panel.clearSelection();
				name.setString("");
				description.setString("");
			}
		}
	}

	return false;
}
