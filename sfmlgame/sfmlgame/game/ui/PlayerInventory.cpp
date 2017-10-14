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

	button1.setText("Equip");

	selectedItem = 0;

	weaponSlot.OnClick([=]() {
		this->onWeaponSlotClick();
	});
	updateTimer = 1.f;
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

	button1.draw();

	weaponSlot.draw();
	GameWindow::getInternalHandle().draw(name);
	GameWindow::getInternalHandle().draw(description);
	GameWindow::getInternalHandle().setView(oldView);
}

void PlayerInventory::update(float dt)
{
	if (!show)
		return;
	updateTimer -= dt;
	if (updateTimer < 0.f)
	{
		updateTimer = 1.f;
		panel.updatePanel();
		weaponSlot.setItem(player->getInventorySlots().getWeapon());
	}

	if (button1.isClicked())
	{
		Inventory::Item* item = panel.getItem(selectedItem);
		if (item != 0)
		{
			ItemManager::Item info = ItemManager::getItem(item->info.name);

			if (info.type == "weapon")
			{
				PlayerSlots& slots = player->getInventorySlots();
				if (slots.setWeapon(item->info))
				{
					weaponSlot.setItem(slots.getWeapon());
					panel.removeItem(selectedItem);
					player->updateInventorySlots();
				}
				/*if (player->getWeaponName() == info.weaponType)
				{
					player->setWeapon("fists");
					weaponSlot.clear();
				}
				else
				{
					player->setWeapon(info.weaponType);
					weaponSlot.setItem(selectedItem->info);
				}*/
				updateSelection();
			}
		}
	}

	button1.update(dt);
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

	button1.setPos(Vec2f::add(centerPanel,Vec2f(5.f, 805.f)));
	button1.setSize(Vec2f(200.f, 70.f));

	name.setPosition(centerPanel.toSFMLVec()+sf::Vector2f(810.f,10.f));
	description.setPosition(centerPanel.toSFMLVec() + sf::Vector2f(810.f, 80.f));

	weaponSlot.setPos(Vec2f::add(centerPanel, Vec2f(backgroundSize.x-400.f,160.f)));
	weaponSlot.setSize(Vec2f(600.f, 150.f));
}

void PlayerInventory::toggle()
{
	show = !show;
}

bool PlayerInventory::handleEvent(sf::Event event)
{
	if (!show)
		return false;

	if (button1.handleEvent(event, guiView))
		return true;

	if (weaponSlot.handleEvent(event, guiView))
		return true;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			Vec2f mousePos = GameWindow::getInternalHandle().mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), guiView);

			selectedItem = panel.getAt(mousePos);

			updateSelection();
		}
	}

	return false;
}

void PlayerInventory::updateSelection()
{
	Inventory::Item* item = panel.getItem(selectedItem);
	if (item != 0)
	{
		
		panel.selectItem(item->pos, item->size);

		ItemManager::Item info = ItemManager::getItem(item->info.name);
		name.setString(info.textName);
		description.setString(info.description);

		button1.setText("Use");

		if (info.type == "weapon")
		{
			if (player->getWeaponName() == info.weaponType)
			{
				button1.setText("Remove");
			}
			else
			{
				button1.setText("Equip");
			}
		}
	}
	else
	{
		panel.clearSelection();
		name.setString("");
		description.setString("");
	}
}

void PlayerInventory::onWeaponSlotClick()
{
	PlayerSlots& slots = player->getInventorySlots();
	Inventory::ItemInfo wep = slots.getWeapon();
	if (wep.name == "")
		return;
	
	if (panel.addItem(wep))
	{
		slots.clearWeapon();
		weaponSlot.clear();
		player->updateInventorySlots();
		panel.updatePanel();
	}
}
