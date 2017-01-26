#ifndef PANEL_H
#define PANEL_H

#include "Widget.h"

#include <SFML/Graphics.hpp>
#include <functional>
#include "NinePatchImage.h"

class GuiHandler;

class Panel :public Widget
{
public:
	Panel();
	virtual ~Panel();

	void draw();
	void handleEvent(WidgetEvent& event);
	void redraw();
	void init(GuiHandler* handler);
	void setColor(sf::Color color);
	void OnDrag(std::function<void(Panel*, MouseMoveEvent, Vec2f)> f);

	void setTexture(std::string texture);
protected:
private:
	sf::RectangleShape box;
	NinePatchImage im;
	std::function<void(Panel*, MouseMoveEvent, Vec2f)> onDrag;
	bool isDraging;
	Vec2f storedPos;
};

#endif // PANEL_H
