#ifndef SLIDER_H
#define SLIDER_H

#include "Widget.h"
#include "NinePatchImage.h"
#include <string>
#include "Button.h"

class Slider :public Widget
{
public:
	Slider();
	virtual ~Slider();

	void draw();
	void handleEvent(WidgetEvent& event);
	void redraw();
	void init(GuiHandler* handler);

	void setValue(float v);
	float getValue();
	void setVertical(bool vert);

	void OnValueChange(std::function<void(Slider*, float)> f);
	void onVisibityChange();
protected:
private:
	void onButton(Button* sender, MouseDownEvent e);

	void updateSlider();
	float calculateValue(Vec2f p);

	std::function<void(Slider*, float)> onValueChange;

	NinePatchImage im;
	sf::RectangleShape box;
	Button* up;
	Button* down;
	float value;
	bool isVertical;
	bool isDraging;
};

#endif // SLIDER_H
