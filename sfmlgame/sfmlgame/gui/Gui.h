#ifndef GUI_H
#define GUI_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Widget.h"
#include "GuiHandler.h"

class Gui
{
public:
	Gui();
	virtual ~Gui();

	void draw();
	bool handleEvent(sf::Event& event);
	void add(Widget* widget, std::string id = "");
	static sf::Font& getDefaultFont();
	Widget* findById(std::string id);
	sf::View getView();
	void triggerResize();
protected:
private:
	GuiHandler handler;
};

#endif // GUI_H
