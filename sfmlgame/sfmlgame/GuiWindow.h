#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include "Widget.h"
#include "GuiHandler.h"

#include <SFML/Graphics.hpp>
#include <functional>

class Panel;

class GuiWindow : public Widget
{
public:
	GuiWindow();
	virtual ~GuiWindow();

	void init(GuiHandler* handler);
	void draw();
	void handleEvent(WidgetEvent& event);
	void redraw();
	void add(Widget* widget, std::string id = "");
	Widget* findById(std::string id);
protected:
private:
	void onDrag(Panel* sender, MouseMoveEvent e, Vec2f delta);
	GuiHandler gui;
	Panel* panel;
	Panel* panel2;
	float titlebar;
	bool ignoreS;
};

#endif // GUIWINDOW_H
