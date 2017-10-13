#pragma once
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>
class Player;

class PlayerUi
{
public:
	PlayerUi();
	~PlayerUi();

	void setPlayer(Player* player);
	void resize(sf::View view);

	void draw();
private:
	Player* player;
	sf::Text ammoText;
};

