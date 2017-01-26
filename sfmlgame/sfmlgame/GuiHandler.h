#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <memory>
#include <vector>
#include "Widget.h"
#include <SFML/Graphics/View.hpp>

class GuiHandler :public Widget
{
public:
	GuiHandler();
	virtual ~GuiHandler();

	void draw();
	void handleEvent(WidgetEvent& event);
	void add(Widget* widget, std::string id = "");
	void redraw();
	sf::View getView();
	void setView(sf::View view);
	void init(GuiHandler* handler);
	Widget* findById(std::string id);

protected:
private:
	sf::View guiView;
	std::vector<std::unique_ptr<Widget> > childs;
};

#endif // GUIHANDLER_H
