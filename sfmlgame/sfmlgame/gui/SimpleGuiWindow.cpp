#include "SimpleGuiWindow.h"
#include "EditBox.h"
#include "Util.h"
#include "TextLine.h"

SimpleGuiWindow::SimpleGuiWindow(std::vector<SimpleWidget> widgets, Style style)
{
	this->style = style;
	this->widgets = widgets;
	setSize(Vec2f(300.f, 200.f));
}


SimpleGuiWindow::~SimpleGuiWindow()
{
}

void SimpleGuiWindow::draw()
{
	gui.draw();
}

void SimpleGuiWindow::handleEvent(WidgetEvent & event)
{
	gui.handleEvent(event);
}

void SimpleGuiWindow::redraw()
{
	gui.redraw();
}

void SimpleGuiWindow::init(GuiHandler * handler)
{
	Vec2f size = handler->getView().getSize();
	float windowHeight = 0.f;
	windowWidth = getSize().x;
	
	window = new GuiWindow();
	gui.add(window, "window");
	window->setPos(Vec2f::mul(size, 0.5f));

	for (auto& widget : widgets)
	{
		if (widget.type == SimpleWidget::Type::EditBox)
		{
			windowHeight += 20.f;

			TextLine* text = new TextLine();
			text->setText(widget.editbox.name);
			text->setTextSize(12u);
			text->setSize(text->getBestSize());
			text->setPos(Vec2f(text->getSize().x / 2.f + 4.f, windowHeight));
			window->add(text);

			float centerpos = ((text->getSize().x / 2.f + 10.f) + windowWidth)/2.f;
			float freespace = windowWidth - (text->getSize().x / 2.f + 10.f);
			freespace = floor(freespace);

			EditBox* edit = new EditBox();
			edit->setText(widget.editbox.text);
			edit->setTextSize(14u);
			edit->setSize(Vec2f(freespace-20.f, 30.f));
			edit->setPos(Vec2f(centerpos, windowHeight));
			edit->setTexture("editbox");
			window->add(edit);

			widgetMap[widget.id].push_back(edit);

			windowHeight += 20.f;
		}
		if (widget.type == SimpleWidget::Type::TextLine)
		{
			TextLine* text = new TextLine();
			text->setText(widget.textLine.text);
			text->setTextSize(12u);
			text->setSize(text->getBestSize());

			windowHeight += 10.f;

			if (widget.textLine.centered)
				text->setPos(Vec2f(windowWidth/2.f, windowHeight));
			else
				text->setPos(Vec2f(text->getSize().x / 2.f + 6.f, windowHeight));
			
			window->add(text);

			windowHeight += text->getBestSize().y+1.f;
		}
	}
	windowHeight += 36.f;

	if (style == Style::Ok || style == Style::OkCancel)
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(windowWidth-40.f, windowHeight -20.f));
		button1->setSize(Vec2f(60.f, 24.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Ok");
		button1->setMult(0.2f);
		button1->OnClick(std::bind(&SimpleGuiWindow::onOkButton, this, std::placeholders::_1, std::placeholders::_2));
		window->add(button1, "okbutton");
	}
	if (style == Style::OkCancel)
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(windowWidth - 110.f, windowHeight - 20.f));
		button1->setSize(Vec2f(60.f, 24.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Cancel");
		button1->setMult(0.2f);
		button1->OnClick(std::bind(&SimpleGuiWindow::onCancelButton, this, std::placeholders::_1, std::placeholders::_2));
		window->add(button1, "cancelbutton");
	}
	window->setSize(Vec2f(windowWidth, windowHeight));
	//window->hide();
}

void SimpleGuiWindow::OnOk(std::function<bool(std::unordered_map<std::string, Result>&)> func)
{
	okcallback = func;
}

void SimpleGuiWindow::getResults()
{
	for (auto& widget : widgets)
	{
		if (widget.type == SimpleWidget::Type::EditBox)
		{
			Result result;
			result.type = widget.type;
			result.editBox.text = ((EditBox*)widgetMap.at(widget.id)[0])->getText();
			results[widget.id] = result;
		}
	}
}

void SimpleGuiWindow::onCancelButton(Button* sender, MouseDownEvent event)
{
	destroy();
}

void SimpleGuiWindow::onOkButton(Button * sender, MouseDownEvent event)
{
	getResults();

	if (okcallback)
	{
		if (okcallback(results))
		{
			destroy();
		}
	}
	else
	{
		destroy();
	}
}
