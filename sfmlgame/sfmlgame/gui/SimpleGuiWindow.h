#pragma once
#include "Widget.h"
#include "GuiWindow.h"
#include "Button.h"
#include <vector>
#include <unordered_map>
#include "GuiHandler.h"

struct SimpleWidget
{
	enum class Type
	{
		EditBox,
		TextLine
	};

	SimpleWidget(std::string id, Type type)
	{
		this->type = type;
		this->id = id;
	}

	static SimpleWidget EditBox(std::string id,std::wstring name, std::wstring text = L"")
	{
		SimpleWidget wid(id, Type::EditBox);

		wid.editbox.name = name;
		wid.editbox.text = text;
		return wid;
	}

	static SimpleWidget TextLine(std::wstring text, bool centered = false)
	{
		SimpleWidget wid("", Type::TextLine);

		wid.textLine.text = text;
		wid.textLine.centered = centered;
		return wid;
	}

	Type type;
	std::string id;

	struct EditBox
	{
		std::wstring text;
		std::wstring name;
	} editbox;
	struct TextLine
	{
		std::wstring text;
		bool centered;
	} textLine;
};

class SimpleGuiWindow :
	public Widget
{
public:
	enum class Style
	{
		OkCancel,
		Ok
	};

	struct Result
	{
		SimpleWidget::Type type;

		struct EditBox
		{
			std::wstring text;
		}editBox;
	};

	SimpleGuiWindow(std::vector<SimpleWidget> widgets, Style style = Style::OkCancel);
	virtual ~SimpleGuiWindow();

	void draw();
	void handleEvent(WidgetEvent& event);
	void redraw();
	void init(GuiHandler* handler);

	void OnOk(std::function<bool(std::unordered_map< std::string, Result>&)> func);

private:
	void getResults();
	void onCancelButton(Button* sender, MouseDownEvent event);
	void onOkButton(Button* sender, MouseDownEvent event);

	GuiWindow* window;
	Button* ok;
	Button* cancel;
	Style style;
	float windowWidth;

	std::vector<SimpleWidget> widgets;
	std::unordered_map< std::string, std::vector<Widget*> > widgetMap;
	std::unordered_map< std::string, Result > results;

	GuiHandler gui;

	std::function<bool(std::unordered_map< std::string, Result>&)> okcallback;
};

