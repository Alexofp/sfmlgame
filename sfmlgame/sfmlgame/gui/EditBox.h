#ifndef EDITBOX_H
#define EDITBOX_H

#include "Widget.h"
#include "NinePatchImage.h"
#include <string>

#include "Button.h"

class EditBox :public Widget
{
public:
	EditBox();
	virtual ~EditBox();

	void draw();
	void handleEvent(WidgetEvent& event);
	void redraw();
	void init(GuiHandler* handler);
	void setTexture(std::string texture);
	void setTextSize(unsigned int size);
	void setText(std::wstring str);
	std::wstring getText();
protected:
private:
	NinePatchImage im;
	sf::Text text;
	std::wstring str;
	bool isFocused;

};

#endif // EDITBOX_H
