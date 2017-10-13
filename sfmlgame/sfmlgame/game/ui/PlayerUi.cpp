#include "PlayerUi.h"
#include "Player.h"
#include "Gui.h"
#include "GameWindow.h"

PlayerUi::PlayerUi()
{
	player = 0;
	ammoText.setFont(Gui::getDefaultFont());
	ammoText.setFillColor(sf::Color::White);
	ammoText.setOutlineColor(sf::Color::Black);
	ammoText.setOutlineThickness(1.f);
	ammoText.setString("10/100");
}


PlayerUi::~PlayerUi()
{
}

void PlayerUi::setPlayer(Player * player)
{
	this->player = player;
}

void PlayerUi::resize(sf::View view)
{
	ammoText.setPosition(sf::Vector2f(10.f, view.getSize().y - 100.f));
}

void PlayerUi::draw()
{
	if (player == 0)
		return;

	if (player->isReloading())
	{
		ammoText.setString("Reloading");
	}
	else
	{
		if (player->getClipSize() == 0)
		{
			ammoText.setString("");
		}
		else
		{
			ammoText.setString(std::to_string(player->getClip())+"/"+std::to_string( player->getInventory().getAmmoCount(player->getRequiredAmmo()) ));
		}
	}

	GameWindow::getInternalHandle().draw(ammoText);
}
