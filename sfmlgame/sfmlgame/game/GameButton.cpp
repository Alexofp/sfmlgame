#include "GameButton.h"
#include "GameWindow.h"
#include "gui.h"
#include "Util.h"

GameButton::GameButton()
{
	shape.setFillColor(sf::Color(0, 0, 0));
	shape.setOutlineColor(sf::Color(255, 255, 255));
	shape.setOutlineThickness(2);

	text.setFont(Gui::getDefaultFont());
	text.setCharacterSize(32u);
	text.setFillColor(sf::Color(255, 255, 255));
}


GameButton::~GameButton()
{
}

void GameButton::setPos(Vec2f pos)
{
	this->pos = pos;
	dirty = true;
}

void GameButton::setSize(Vec2f size)
{
	this->size = size;
	dirty = true;
}

bool GameButton::handleEvent(sf::Event event, sf::View guiView)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		Vec2f mousePos = GameWindow::getInternalHandle().mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), guiView);
	
		if (Util::boxCollision2(pos, size, mousePos, Vec2f(1.f, 1.f)))
		{
			clicked = true;
			return true;
		}
	}

	return false;
}

void GameButton::updateShape()
{
	shape.setPosition(pos.toSFMLVec());
	shape.setSize(size.toSFMLVec());

	Vec2f center = Vec2f::add(pos, Vec2f::mul(size, 0.5f));
	text.setPosition(center.toSFMLVec());
	sf::FloatRect bounds = text.getLocalBounds();
	float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());
	text.setOrigin(bounds.width / 2, lineSpacing / 2);
}

void GameButton::setText(std::string str)
{
	text.setString(str);
	dirty = true;
}

bool GameButton::isClicked()
{
	return clicked;
}

void GameButton::update(float dt)
{
	clicked = false;
}

void GameButton::draw()
{
	if (dirty)
	{
		dirty = false;
		updateShape();
	}

	GameWindow::getInternalHandle().draw(shape);
	GameWindow::getInternalHandle().draw(text);
}
