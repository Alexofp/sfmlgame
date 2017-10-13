#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "Vec2f.h"

class HealthBar
{
public:
	HealthBar();
	~HealthBar();

	void setPos(Vec2f pos);
	void draw();
	void setHealth(int hp);
	void setMaxHealth(int hp);
private:
	void updateShape();
	Vec2f getFinalPos();

	bool dirty;
	sf::RectangleShape background;
	sf::RectangleShape healthShape;
	int hp;
	int maxHp;
	Vec2f pos;
	Vec2f size;
};

