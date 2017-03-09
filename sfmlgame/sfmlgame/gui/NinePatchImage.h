#ifndef NINEPACHIMAGE_H
#define NINEPACHIMAGE_H

#include <SFML/Graphics.hpp>
#include "Vec2f.h"
#include <string>
#include <vector>

class NinePatchImage
{
public:
	NinePatchImage();
	virtual ~NinePatchImage();

	void draw();
	void redraw();
	void setTexture(std::string texture);
	void setTextureRect(Vec2f textureRect);
	void setMult(float m);
	void setColor(sf::Color color);

	void setPos(Vec2f pos);
	void setSize(Vec2f size);
	Vec2f getPos();
	Vec2f getSize();
protected:
private:
	Vec2f pos;
	Vec2f size;
	std::string texture;
	Vec2f textureRect;
	float mult;
	bool shouldUpdate;
	sf::Color color;

	std::vector<sf::RectangleShape> shapes;
};

#endif // NINEPACHIMAGE_H
