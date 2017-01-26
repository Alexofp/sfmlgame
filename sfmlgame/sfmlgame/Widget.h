#ifndef WIDGET_H
#define WIDGET_H

#include "Vec2f.h"
#include "Vec2i.h"
#include <string>

enum class WidgetEventType
{
	MouseDown,
	MouseUp,
	MouseMove,
	Resized,
	TextEntered
};

struct ResizedEvent
{
	Vec2f size;
};

struct MouseDownEvent
{
	int button;
	Vec2f pos;
};

struct MouseUpEvent
{
	int button;
	Vec2f pos;
};

struct MouseMoveEvent
{
	Vec2f pos;
};

struct TextEnteredEvent
{
	int key;
};

struct WidgetEvent
{
	bool handled;
	WidgetEventType type;

	MouseDownEvent mouseDown;
	MouseUpEvent mouseUp;
	MouseMoveEvent mouseMove;
	ResizedEvent resized;
	TextEnteredEvent textEntered;
	Vec2i originalMousePos;
};

class GuiHandler;

class Widget
{
public:
	Widget();
	virtual ~Widget();

	virtual void draw() = 0;
	virtual void handleEvent(WidgetEvent& event) = 0;
	virtual void redraw() = 0;
	virtual void init(GuiHandler* handler) = 0;
	virtual void onVisibityChange();

	void setPos(Vec2f pos);
	void setSize(Vec2f size);
	Vec2f getPos();
	Vec2f getSize();
	void show();
	void hide();
	bool isVisible();
	void setId(std::string id);
	std::string getId();
	void setHandler(GuiHandler* handler);


	Vec2i getRealPos();
protected:
	bool shouldUpdate;
private:
	GuiHandler* handler;
	std::string id;
	bool visible;
	Vec2f pos;
	Vec2f size;
};

#endif // WIDGET_H
