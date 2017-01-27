#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include "NinePatchImage.h"

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class GuiHandler;

class Button :public Widget
{
public:
	Button();
	virtual ~Button();

	void draw();
	void handleEvent(WidgetEvent& event);
	void redraw();
	void OnClick(std::function<void(Button*, MouseDownEvent)> func);
	void init(GuiHandler* handler);
	void setTexture(std::string texture);
	void setText(std::wstring str);
	void setMult(float m);

	void setColor(sf::Color color);
	void setTextSize(unsigned int size);
protected:
private:
	sf::RectangleShape box;
	sf::Text text;
	std::function<void(Button*, MouseDownEvent)> onClick;
	NinePatchImage im;
	float mult;
};

#endif // BUTTON_H
