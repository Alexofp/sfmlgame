#include "TextLine.h"
#include "Util.h"
#include <iostream>
#include "GameWindow.h"
#include "Gui.h"

TextLine::TextLine() :Widget()
{
	shouldUpdate = true;
	text.setString("Button");
	setTextSize(16);
	text.setFont(Gui::getDefaultFont());
}

TextLine::~TextLine()
{
}

void TextLine::draw()
{
	if (shouldUpdate)
	{
		redraw();
		shouldUpdate = false;
	}

	GameWindow::getInternalHandle().draw(text);
}

void TextLine::handleEvent(WidgetEvent& event)
{
}

void TextLine::setColor(sf::Color color)
{
	text.setFillColor(color);
}

void TextLine::setTextSize(unsigned int size)
{
	text.setCharacterSize(size);
	shouldUpdate = true;
}

void TextLine::redraw()
{
	sf::FloatRect boundingBox = text.getLocalBounds();

	float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());

	text.setPosition(sf::Vector2f(getPos().getX(), getPos().getY()));
	text.setOrigin(boundingBox.width / 2, lineSpacing / 2);
}


void TextLine::init(GuiHandler* handler)
{
}

void TextLine::setText(std::wstring str)
{
	text.setString(str);
	sf::FloatRect boundingBox = text.getLocalBounds();

	float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());

	text.setPosition(sf::Vector2f(getPos().getX(), getPos().getY()));
	text.setOrigin(boundingBox.width / 2, lineSpacing / 2);
}

void TextLine::setText(std::string str)
{
	std::wstring text = Util::strToWStr(str);
	setText(text);
}

Vec2f TextLine::getBestSize()
{
	sf::FloatRect boundingBox = text.getLocalBounds();

	return Vec2f(boundingBox.width, boundingBox.height);
}
