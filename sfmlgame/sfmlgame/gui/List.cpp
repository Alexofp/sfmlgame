#include "List.h"
#include "Util.h"
#include <iostream>
#include "GameWindow.h"
#include "Gui.h"
#include "Slider.h"
#include <SFML/OpenGL.hpp>

List::List() :Widget()
{
	//ctor
	im.setTexture("editbox");
	im.setTextureRect(Vec2f(10.f, 10.f));

	scrollMax = 0.f;
	scrollPos = 0.f;

	cutSizeH = Vec2i(2, 2);
	cutSize = Vec2i(2, 2);

	selectedBox.setFillColor(sf::Color(100, 100, 100));

	showSlider = false;
}

List::~List()
{
	//dtor
}

void List::draw()
{
	if (shouldUpdate)
	{
		shouldUpdate = false;
		redraw();
	}

	im.draw();

	glEnable(GL_SCISSOR_TEST);
	glScissor(getRealPos().getX() - getSize().getX() / 2.f + cutSizeH.getX(), cutSize.getX() + GameWindow::getInternalHandle().getSize().y - getRealPos().getY() - getSize().getY() / 2.f, getSize().getX() - 20 - cutSizeH.getX() - cutSizeH.getY(), getSize().getY() - cutSize.getX() - cutSize.getY());

	//sf::View v = Window::getWindow().getView();
	//sf::View oldV = v;
	//v.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

	//Window::getWindow().setView(v);

	if (selectedIndex > 0 && selectedIndex < itemsText.size())
	{
		auto text = itemsText[selectedIndex];
		Vec2f textPos(text.getPosition());
		selectedBox.setPosition(textPos.toSFMLVec());
	}
	GameWindow::getInternalHandle().draw(selectedBox);


	for (auto& item : itemsText)
	{
		GameWindow::getInternalHandle().draw(item);
	}

	//Window::getWindow().setView(oldV);

	glDisable(GL_SCISSOR_TEST);
}

void List::OnListSelect(std::function<void(List*, ListItem)> f)
{
	onListSelect = f;
}

void List::handleEvent(WidgetEvent& event)
{
	if (!event.handled)
	{
		//std::cout << "Event" << std::endl;
		if (event.type == WidgetEventType::MouseDown)
		{
			if (Util::boxCollision(event.mouseDown.pos, Vec2f(1.f, 1.f), Vec2f::sub(getPos(), Vec2f(10.f, 0.f)), Vec2f::sub(getSize(), Vec2f(20.f, 0.f))))
			{
				event.handled = true;
				int i = 0;
				for (auto& text : itemsText)
				{
					float lineSpacing = Gui::getDefaultFont().getLineSpacing(itemsText[0].getCharacterSize());

					Vec2f textPos(text.getPosition());
					Vec2f textSize(getSize().getX(), lineSpacing);

					if (Util::boxCollision(event.mouseDown.pos, Vec2f(1.f, 1.f), textPos, textSize))
					{
						selectedIndex = i;
						selectedBox.setPosition(textPos.toSFMLVec());
						selectedBox.setSize(textSize.toSFMLVec());
						selectedBox.setOrigin(textSize.toSFMLVec() / 2.f);

						if (onListSelect)
						{
							onListSelect(this, items[selectedIndex]);
						}
						break;
					}
					i++;
				}
			}
		}
	}
}

void List::checkSlider()
{
	if (itemsText.size() == 0)
	{
		return;
	}
	float lineSpacing = Gui::getDefaultFont().getLineSpacing(itemsText[0].getCharacterSize());
	scrollMax = getSize().getY() - itemsText.size()*lineSpacing - 4.f;
	if (scrollMax > 0.f)
	{
		scrollMax = 0.f;
		slider->hide();
		showSlider = false;
	}
	else
	{
		slider->show();
		showSlider = true;
	}


	scrollPos = scrollMax*slider->getValue();
	updateText();
}

void List::onSlider(Slider* sender, float value)
{
	checkSlider();
}

void List::updateText()
{
	int i = 0;
	float curH = 0.f;

	for (auto& text : itemsText)
	{
		sf::FloatRect boundingBox = text.getLocalBounds();
		float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());
		text.setPosition(sf::Vector2f(getPos().getX(), getPos().getY() - getSize().getY() / 2.f + boundingBox.height / 2.f + 4.f + curH + scrollPos));
		text.setOrigin(-4.f + getSize().getX() / 2.f, lineSpacing / 2);

		curH += lineSpacing;
		i++;
	}
}

void List::redraw()
{
	im.setPos(Vec2f::sub(getPos(), Vec2f(10.f, 0.f)));
	im.setSize(Vec2f::sub(getSize(), Vec2f(20.f, 0.f)));

	slider->setSize(Vec2f(20.f, getSize().getY()));
	slider->setPos(Vec2f(getPos().getX() + getSize().getX() / 2.f - 20.f / 2.f, getPos().getY()));

	itemsText.clear();

	int i = 0;
	float curH = 0.f;
	for (auto& item : items)
	{
		sf::Text text;
		text.setFont(Gui::getDefaultFont());
		text.setCharacterSize(12);
		text.setString(item.text);

		sf::FloatRect boundingBox = text.getLocalBounds();
		float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());
		text.setPosition(sf::Vector2f(getPos().getX(), getPos().getY() - getSize().getY() / 2.f + boundingBox.height / 2.f + 4.f + curH));
		text.setOrigin(-4.f + getSize().getX() / 2.f, lineSpacing / 2);

		curH += lineSpacing;

		itemsText.push_back(text);

		i++;
	}
	checkSlider();
}

void List::init(GuiHandler* handler)
{
	slider = new Slider();
	slider->setPos(Vec2f(180.f, 250.f));
	slider->setSize(Vec2f(20.f, 300.f));
	slider->setVertical(true);
	slider->OnValueChange(std::bind(&List::onSlider, this, std::placeholders::_1, std::placeholders::_2));
	handler->add(slider);

	gui = handler;
}

void List::addItem(std::wstring text, std::string id)
{
	ListItem item;
	item.text = text;
	item.id = id;

	items.push_back(item);
	shouldUpdate = true;
}

void List::addItem(std::string text, std::string id)
{
	std::wstring wtext(text.begin(), text.end());

	addItem(wtext, id);
}

void List::removeItem(std::string id)
{
	int i = 0;
	for (auto& item : items)
	{
		if (item.id == id)
		{
			items.erase(items.begin() + i);
			return;
		}
		i++;
	}
	shouldUpdate = true;
}

void List::clearItems()
{
	items.clear();
	shouldUpdate = true;
}

std::vector<ListItem> List::getItems()
{
	return items;
}

ListItem* List::getSelected()
{
	if (selectedIndex >= 0 && selectedIndex < itemsText.size())
	{
		return &(items[selectedIndex]);
	}
	return nullptr;
}

void List::setSelected(std::string id)
{
	int i = 0;
	for (auto& text : itemsText)
	{
		float lineSpacing = Gui::getDefaultFont().getLineSpacing(itemsText[0].getCharacterSize());

		Vec2f textPos(text.getPosition());
		Vec2f textSize(getSize().getX(), lineSpacing);

		if (items[i].id == id)
		{
			selectedIndex = i;
			selectedBox.setPosition(textPos.toSFMLVec());
			selectedBox.setSize(textSize.toSFMLVec());
			selectedBox.setOrigin(textSize.toSFMLVec() / 2.f);
			return;
		}
		i++;
	}
}

void List::onVisibityChange()
{
	if (!isVisible())
	{
		slider->hide();
	}
	else
		if (showSlider)
		{
			slider->show();
		}
}
