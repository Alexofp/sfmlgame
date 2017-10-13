#include "Player.h"
#include "Input.h"
#include "Log.h"
#include "GameWorld.h"
#include "GameWindow.h"
#include "Settings.h"
#include "AnimationManager.h"

Player::Player(int nid):Person(nid)
{
	this->isRemote = false;
	realType = Type::Player;
	Log::debug("new player entity");

	inventory.setSize(Vec2i(10, 10));
	inventory.addItem(Inventory::Item(Vec2i(0, 0), "test"));
	inventory.addItem(Inventory::Item(Vec2i(0, 2), "ak74"));

	Inventory::ItemInfo info;
	info.name = "riffle_ammo";
	info.ammo.count = 90;
	inventory.addItemAnywhere(Inventory::Item(Vec2i(0, 0), info));

	setWeapon("fists", false);
	clip = 0;
	updateInventorySlots();
}


Player::~Player()
{
}

void Player::init()
{
	Person::init();
}

void Player::update(float dt)
{
	updateSkeleton(dt);
}

void Player::localUpdate(float dt)
{
	if (!isRemote)
	{
		moveControl = Vec2f();
		if (Input::getKey(Input::A))
			moveControl.x = -1;
		if (Input::getKey(Input::D))
			moveControl.x = 1;
		if (Input::getKey(Input::W))
			moveControl.y = -1;
		if (Input::getKey(Input::S))
			moveControl.y = 1;

		if (Input::getMouseDown(Input::MouseLeft) || (weapon.info.autoFire && Input::getMouse(Input::MouseLeft)))
			attack();

		lookPosition = Input::getWorldMousePos();
	}

	updateSkeleton(dt);

	if (!isRemote)
	{
		GameWindow::setCameraCenter(getPos());
	}
}

void Player::draw()
{
	Person::draw();
}

void Player::setRemote(bool isRemote)
{
	this->isRemote = isRemote;
}

void Player::setClientId(int clientId)
{
	this->clientId = clientId;
}

int Player::getClientId()
{
	return clientId;
}

void Player::reload()
{
	if (weapon.info.ammoPerShot == 0)
		return;

	if (!isReload)
	{
		clip = inventory.removeAmmo(getRequiredAmmo(), weapon.info.clipSize);

		if (clip > 0)
		{
			isReload = true;
			reloadTimer = 1.f;
		
			Log::debug("I'm reloading");
		}
	}
}

void Player::unloadWeapon()
{
	if (clip > 0 && weapon.info.usesAmmo != "")
	{
		Inventory::ItemInfo info;
		info.name = weapon.info.usesAmmo;
		info.ammo.count = clip;
		inventory.addItemAnywhere(Inventory::Item(Vec2i(0, 0), info));
		clip = 0;
	}
}

void Player::writeInformation(sf::Packet & packet)
{
	packet << getBodyPos();
	packet << getBodySpeed();
	packet << lookPosition;
	packet << moveControl;
}

void Player::readInformation(sf::Packet & packet)
{
	Vec2f newpos;
	Vec2f newspeed;
	Vec2f look;
	Vec2f control;

	packet >> newpos >> newspeed >> look >> control;

	if (isRemote)
	{
		setBodyPos(newpos);
		speed = newspeed;
		setBodySpeed(newspeed);
		lookPosition = look;
		moveControl = control;
	}
}

void Player::writeSpawn(sf::Packet & packet)
{
	packet << (sf::Int16)getClientId();
	packet << getBodyPos();
	packet << getBodySpeed();
	packet << lookPosition;
}

void Player::readSpawn(sf::Packet & packet)
{
	sf::Int16 clientId;
	Vec2f newpos;
	Vec2f newspeed;
	Vec2f look;

	packet >> clientId >> newpos >> newspeed >> look;

	setClientId(clientId);
	setBodyPos(newpos);
	speed = newspeed;
	setBodySpeed(newspeed);
	lookPosition = look;
}

PlayerSlots & Player::getInventorySlots()
{
	return inventorySlots;
}

void Player::updateInventorySlots()
{
	Inventory::ItemInfo weaponSlotInfo = inventorySlots.getWeapon();

	if (weaponSlotInfo.name == "")
	{
		unloadWeapon();
		setWeapon("fists");
	}
	else
	{
		ItemManager::Item info = ItemManager::getItem(weaponSlotInfo.name);
		if (info.type != "weapon" || info.weaponType == "")
		{
			unloadWeapon();
			setWeapon("fists");
		}
		else
		{
			if (getWeaponName() != info.weaponType)
			{
				unloadWeapon();
				setWeapon(info.weaponType, false);
			}
		}
	}


}
