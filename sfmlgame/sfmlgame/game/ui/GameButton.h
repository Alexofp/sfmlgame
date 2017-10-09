#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include "Vec2f.h"

class GameButton
{
public:
	GameButton();
	~GameButton();

	void setPos(Vec2f pos);
	void setSize(Vec2f size);

	bool handleEvent(sf::Event event, sf::View guiView);
	void updateShape();
	void setText(std::string text);
	bool isClicked();
	void update(float dt);

	void draw();
private:
	sf::RectangleShape shape;
	Vec2f pos;
	Vec2f size;
	bool dirty;
	sf::Text text;
	bool clicked;
};

