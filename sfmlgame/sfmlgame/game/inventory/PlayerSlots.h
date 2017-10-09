#pragma once
#include "ItemManager.h"
#include "Inventory.h"

class PlayerSlots
{
public:
	PlayerSlots();
	~PlayerSlots();

	void clearWeapon();
	bool setWeapon(Inventory::ItemInfo info);
	Inventory::ItemInfo& getWeapon();

private:
	Inventory::ItemInfo head;
	Inventory::ItemInfo body;
	Inventory::ItemInfo legs;
	Inventory::ItemInfo boots;
	Inventory::ItemInfo weapon;
};

