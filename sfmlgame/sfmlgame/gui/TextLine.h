#pragma once
#include "Widget.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class TextLine :public Widget
{
public:
	TextLine();
	virtual ~TextLine();

	void draw();
	void handleEvent(WidgetEvent& event);
	void redraw();
	void init(GuiHandler* handler);
	void setText(std::wstring str);
	void setText(std::string str);
	Vec2f getBestSize();

	void setColor(sf::Color color);
	void setTextSize(unsigned int size);
protected:
private:
	sf::Text text;
};

