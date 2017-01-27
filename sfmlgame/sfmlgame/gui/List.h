#ifndef LIST_H
#define LIST_H

#include "Widget.h"
#include "NinePatchImage.h"

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

struct ListItem
{
	std::wstring text;
	std::string id;
};

class Slider;

class List :public Widget
{
public:
	List();
	virtual ~List();

	void draw();
	void handleEvent(WidgetEvent& event);
	void redraw();
	void init(GuiHandler* handler);

	void addItem(std::wstring text, std::string id = "");
	void addItem(std::string text, std::string id = "");
	void removeItem(std::string id);
	void clearItems();
	std::vector<ListItem> getItems();
	void onVisibityChange();
	ListItem* getSelected();
	void setSelected(std::string id);

	void OnListSelect(std::function<void(List*, ListItem)> f);
protected:
private:
	void onSlider(Slider* sender, float value);
	void updateText();
	void checkSlider();

	std::function<void(List*, ListItem)> onListSelect;

	GuiHandler* gui;

	std::vector<ListItem> items;
	std::vector<sf::Text> itemsText;
	NinePatchImage im;
	Slider* slider;
	Vec2i cutSize;
	Vec2i cutSizeH;
	bool showSlider;

	sf::RectangleShape selectedBox;
	int selectedIndex;

	float scrollMax;
	float scrollPos;
};

#endif // LIST_H
