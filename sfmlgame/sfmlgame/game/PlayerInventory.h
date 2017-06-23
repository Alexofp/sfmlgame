#pragma once
#include "Player.h"
#include "InventoryPanel.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include "gui.h"
#include <SFML/Graphics/Text.hpp>

class PlayerInventory
{
public:
	PlayerInventory();
	~PlayerInventory();

	void setPlayer(Player* player);

	void draw();
	void resize();
	void toggle();

	bool handleEvent(sf::Event event);
private:
	Player* player;
	InventoryPanel panel;
	sf::View guiView;
	sf::RectangleShape background;
	sf::Text name;
	sf::Text description;
	bool show;
};

