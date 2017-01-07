#pragma once
#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Vec2f.h"

class SimpleSprite
{
public:
	SimpleSprite();
	~SimpleSprite();

	void setPos(Vec2f pos);
	void setSize(Vec2f size);
	void setAng(float ang);
	void setTexture(std::string texture);

	Vec2f getPos();
	Vec2f getSize();
	float getAng();

	void draw();
private:
	sf::RectangleShape box;
};

