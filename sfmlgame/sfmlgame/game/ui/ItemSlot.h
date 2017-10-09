#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "Inventory.h"
#include "Vec2f.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>

class ItemSlot
{
public:
	ItemSlot();
	~ItemSlot();

	void clear();
	void setItem(Inventory::ItemInfo info);

	void draw();
	void setPos(Vec2f pos);
	void setSize(Vec2f size);
	bool handleEvent(sf::Event event, sf::View guiView);
	void OnClick(std::function<void()> f);
private:
	Vec2f pos;
	Vec2f size;
	void updateShape();

	bool dirty;
	sf::RectangleShape shape;
	sf::RectangleShape background;
	Inventory::ItemInfo item;
	std::function<void()> onClick;
};

