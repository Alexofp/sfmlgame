#include "Slider.h"
#include "Util.h"
#include <iostream>
#include "GameWindow.h"
#include "Gui.h"
#include "TextureManager.h"

Slider::Slider() :Widget()
{
	//ctor
	im.setTexture("editbox");
	im.setTextureRect(Vec2f(10.f, 10.f));
	isVertical = false;
	value = 0.f;
	isDraging = false;

	box.setTexture(TextureManager::get("button"));

}

Slider::~Slider()
{
	//dtor
}

void Slider::draw()
{
	if (shouldUpdate)
	{
		shouldUpdate = false;
		redraw();
	}
	im.draw();
	GameWindow::getInternalHandle().draw(box);
}

float Slider::calculateValue(Vec2f p)
{
	Vec2f buttonSize(getSize().getY(), getSize().getY());
	if (isVertical)
	{
		buttonSize = Vec2f(getSize().getX(), getSize().getX());
	}

	float v;

	if (!isVertical)
	{
		float sliderSize = getSize().getX() - 3 * buttonSize.getX();
		Vec2f sliderStart = Vec2f::add(getPos(), Vec2f(-getSize().getX() / 2.f + buttonSize.getX()*1.5f, 0.f));

		Vec2f delta = Vec2f::sub(p, sliderStart);
		v = delta.getX() / sliderSize;
	}
	else
	{
		float sliderSize = getSize().getY() - 3 * buttonSize.getY();
		Vec2f sliderStart = Vec2f::add(getPos(), Vec2f(0.f, -getSize().getY() / 2.f + buttonSize.getY()*1.5f));
		Vec2f delta = Vec2f::sub(p, sliderStart);
		v = delta.getY() / sliderSize;
	}

	if (v < 0.f)
		v = 0.f;
	if (v > 1.f)
		v = 1.f;

	return v;
}

void Slider::handleEvent(WidgetEvent& event)
{
	if (!event.handled && event.type == WidgetEventType::MouseDown)
	{
		Vec2f buttonSize(getSize().getY(), 0);
		if (isVertical)
		{
			buttonSize = Vec2f(0, getSize().getX());
		}

		if (Util::boxCollision(event.mouseDown.pos, Vec2f(1.f, 1.f), getPos(), Vec2f::sub(getSize(), Vec2f::mul(buttonSize, 2.f))))
		{
			event.handled = true;

			isDraging = true;

			float oldValue = value;
			value = calculateValue(event.mouseDown.pos);
			if (onValueChange && oldValue != value)
			{
				onValueChange(this, value);
			}
			updateSlider();
			//std::cout << v << std::endl;
		}
	}
	if (isDraging && event.type == WidgetEventType::MouseMove)
	{
		float oldValue = value;
		value = calculateValue(event.mouseMove.pos);
		if (onValueChange && oldValue != value)
		{
			onValueChange(this, value);
		}
		updateSlider();
	}
	if (event.type == WidgetEventType::MouseUp)
	{
		isDraging = false;
	}
}

void Slider::updateSlider()
{
	Vec2f buttonSize(getSize().getY(), getSize().getY());
	float sliderSize = getSize().getX() - 3 * buttonSize.getX();
	if (isVertical)
	{
		buttonSize = Vec2f(getSize().getX(), getSize().getX());
		sliderSize = getSize().getY() - 3 * buttonSize.getY();
	}
	box.setPosition(Vec2f::add(getPos(), Vec2f(-getSize().getX() / 2.f + buttonSize.getX()*1.5f + sliderSize*value, 0.f)).toSFMLVec());
	if (isVertical)
	{
		box.setPosition(Vec2f::add(getPos(), Vec2f(0.f, -getSize().getY() / 2.f + buttonSize.getY()*1.5f + sliderSize*value)).toSFMLVec());
	}
}

void Slider::redraw()
{
	if (isVertical)
	{
		im.setMult(0.02f);
	}

	Vec2f buttonSize(getSize().getY(), getSize().getY());
	if (isVertical)
	{
		buttonSize = Vec2f(getSize().getX(), getSize().getX());
	}
	box.setSize(buttonSize.toSFMLVec());
	box.setOrigin(buttonSize.toSFMLVec() / 2.f);


	updateSlider();



	if (!isVertical)
	{
		im.setPos(getPos());
		im.setSize(Vec2f(getSize().getX() - 2 * buttonSize.getX(), getSize().getY()));

		up->setSize(buttonSize);
		up->setPos(Vec2f::add(getPos(), Vec2f(getSize().getX() / 2.f - buttonSize.getX() / 2.f, 0.f)));

		down->setSize(buttonSize);
		down->setPos(Vec2f::add(getPos(), Vec2f(-getSize().getX() / 2.f + buttonSize.getX() / 2.f, 0.f)));
	}
	else
	{
		im.setPos(getPos());
		im.setSize(Vec2f(getSize().getX(), getSize().getY() - 2 * buttonSize.getY()));

		up->setSize(buttonSize);
		up->setPos(Vec2f::add(getPos(), Vec2f(0.f, getSize().getY() / 2.f - buttonSize.getY() / 2.f)));

		down->setSize(buttonSize);
		down->setPos(Vec2f::add(getPos(), Vec2f(0.f, -getSize().getY() / 2.f + buttonSize.getY() / 2.f)));
	}
}

void Slider::OnValueChange(std::function<void(Slider*, float)> f)
{
	onValueChange = f;
}

void Slider::onButton(Button* sender, MouseDownEvent e)
{
	float oldValue = value;
	if (sender == up)
	{
		value += 0.1f;
		if (value > 1.f)
			value = 1.f;
	}
	else
	{
		value -= 0.1f;
		if (value < 0.f)
			value = 0.f;
	}
	if (onValueChange && oldValue != value)
	{
		onValueChange(this, value);
	}
	updateSlider();
}

void Slider::init(GuiHandler* handler)
{
	up = new Button();
	up->setPos(Vec2f(60.f, 60.f));
	up->setSize(Vec2f(100.f, 40.f));
	up->setMult(0.1f);
	up->OnClick(std::bind(&Slider::onButton, this, std::placeholders::_1, std::placeholders::_2));
	up->setText(L"+");
	up->setTexture("button");
	handler->add(up);

	down = new Button();
	down->setPos(Vec2f(60.f, 60.f));
	down->setSize(Vec2f(100.f, 40.f));
	down->setMult(0.1f);
	down->OnClick(std::bind(&Slider::onButton, this, std::placeholders::_1, std::placeholders::_2));
	down->setTexture("button");
	down->setText(L"-");
	handler->add(down);
}

void Slider::setValue(float v)
{
	value = v;
	updateSlider();
}

float Slider::getValue()
{
	return value;
}

void Slider::setVertical(bool vert)
{
	isVertical = vert;
	shouldUpdate = true;
}

void Slider::onVisibityChange()
{
	if (!isVisible())
	{
		up->hide();
		down->hide();
	}
	else
	{
		up->show();
		down->show();
	}
}