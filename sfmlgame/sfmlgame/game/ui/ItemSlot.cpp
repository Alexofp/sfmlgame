#include "ItemSlot.h"
#include "TextureManager.h"
#include "GameWindow.h"
#include "Util.h"
#include "Log.h"

ItemSlot::ItemSlot()
{
}


ItemSlot::~ItemSlot()
{
}

void ItemSlot::clear()
{
	item = Inventory::ItemInfo();
	item.name = "";
}

void ItemSlot::setItem(Inventory::ItemInfo info)
{
	dirty = true;
	this->item = info;
}

void ItemSlot::draw()
{
	if (dirty)
	{
		dirty = false;
		updateShape();
	}

	GameWindow::getInternalHandle().draw(background);
	if (item.name != "")
	{
		GameWindow::getInternalHandle().draw(shape);
	}
}

void ItemSlot::setPos(Vec2f pos)
{
	this->pos = pos;
	dirty = true;
}

void ItemSlot::setSize(Vec2f size)
{
	this->size = size;
	dirty = true;
}

void ItemSlot::updateShape()
{
	if (item.name != "")
	{
		ItemManager::Item info = ItemManager::getItem(item.name);

		Vec2f itemSize((info.w+1)*50.f, (info.h+1)*50.f);
		shape.setSize(itemSize.toSFMLVec());
		shape.setOrigin(itemSize.toSFMLVec() / 2.f);
		shape.setPosition(pos.toSFMLVec());
		shape.setTexture(TextureManager::get(info.texture));
	}

	background.setSize(size.toSFMLVec());
	background.setOrigin(size.toSFMLVec() / 2.f);
	background.setPosition(pos.toSFMLVec());
}

bool ItemSlot::handleEvent(sf::Event event, sf::View guiView)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		Vec2f mousePos = GameWindow::getInternalHandle().mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), guiView);

		if (Util::boxCollision(pos, size, mousePos, Vec2f(1.f, 1.f)))
		{
			if (onClick)
			{
				onClick();
			}
			return true;
		}
	}

	return false;
}

void ItemSlot::OnClick(std::function<void()> f)
{
	onClick = f;
}
