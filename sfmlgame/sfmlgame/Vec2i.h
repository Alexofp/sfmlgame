#pragma once
#include <SFML/System/Vector2.hpp>

class Vec2i
{
public:
	Vec2i();
	Vec2i(int x, int y);
	Vec2i(sf::Vector2i vec);

	sf::Vector2i toSFMLVec();

	int x, y;
};

