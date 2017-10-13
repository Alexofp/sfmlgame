#pragma once
#include "Player.h"
#include "InventoryPanel.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include "gui.h"
#include <SFML/Graphics/Text.hpp>
#include "GameButton.h"
#include "ItemSlot.h"

class PlayerInventory
{
public:
	PlayerInventory();
	~PlayerInventory();

	void setPlayer(Player* player);

	void draw();
	void update(float dt);
	void resize();
	void toggle();

	bool handleEvent(sf::Event event);
private:
	void updateSelection();
	void onWeaponSlotClick();

	Player* player;
	InventoryPanel panel;
	sf::View guiView;
	sf::RectangleShape background;
	sf::Text name;
	sf::Text description;
	int selectedItem;
	bool show;
	ItemSlot weaponSlot;

	GameButton button1;
	float updateTimer;
};

