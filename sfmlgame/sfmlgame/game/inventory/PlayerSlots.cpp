#include "PlayerSlots.h"



PlayerSlots::PlayerSlots()
{
}


PlayerSlots::~PlayerSlots()
{
}

void PlayerSlots::clearWeapon()
{
	weapon = Inventory::ItemInfo();
}

bool PlayerSlots::setWeapon(Inventory::ItemInfo info)
{
	ItemManager::Item item = ItemManager::getItem(info.name);
	if (item.type != "weapon")
		return false;

	weapon = info;
	return true;
}

Inventory::ItemInfo & PlayerSlots::getWeapon()
{
	return weapon;
}
