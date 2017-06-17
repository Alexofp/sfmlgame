#include "MapEditor.h"
#include "GameWindow.h"
#include "Input.h"
#include "List.h"
#include "Panel.h"
#include "Slider.h"
#include "SimpleGuiWindow.h"
#include "Util.h"
#include "ObjectManager.h"

MapEditor::MapEditor()
{
	terrain.resetSize(Vec2i(5, 5), 6000);
	tool = 0;
	objectAngle = 0.f;

	{
		Panel* panel = new Panel();
		panel->setColor(sf::Color(50, 50, 50, 100));
		gui.add(panel, "rightpanel");
	}
	{
		List* list2 = new List();
		list2->setSize(Vec2f(150.f, 100.f));
		list2->addItem("Texture 1", "tex1");
		list2->addItem("Texture 2", "tex2");
		list2->addItem("Texture 3", "tex3");
		list2->OnListSelect(std::bind(&MapEditor::onTextureSelected, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(list2, "texturelist");
	}
	{
		Slider* slider = new Slider();
		slider->setSize(Vec2f(190.f, 24.f));
		slider->setVertical(false);
		//slider->OnValueChange(std::bind(&AnimationEditor::onSliderMoved, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(slider, "sizeslider");
	}
	{
		Slider* slider = new Slider();
		slider->setSize(Vec2f(190.f, 24.f));
		slider->setVertical(false);
		slider->setValue(1.f);
		//slider->OnValueChange(std::bind(&AnimationEditor::onSliderMoved, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(slider, "colorslider");
	}
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(250.f, 130.f));
		button1->setSize(Vec2f(180.f, 30.f));
		button1->setTextSize(14u);
		button1->setTexture("button");
		button1->setText(L"Новая");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&MapEditor::onNewButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "newbutton");
	}
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(250.f, 130.f));
		button1->setSize(Vec2f(180.f, 30.f));
		button1->setTextSize(14u);
		button1->setTexture("button");
		button1->setText(L"Сохранить");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&MapEditor::onSaveButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "savebutton");
	}
	{
		Button* button1 = new Button();
		button1->setPos(Vec2f(250.f, 130.f));
		button1->setSize(Vec2f(180.f, 30.f));
		button1->setTextSize(14u);
		button1->setTexture("button");
		button1->setText(L"Загрузить");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&MapEditor::onLoadButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "loadbutton");
	}
	{
		List* list2 = new List();
		list2->setSize(Vec2f(150.f, 100.f));
		//list2->addItem("Test", "tex1");
		for (auto& name : ObjectManager::getObjectNames())
		{
			list2->addItem(name, name);
		}
		list2->OnListSelect(std::bind(&MapEditor::onObjectSelected, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(list2, "objectlist");
	}

	textureMode = -1;
	mapName = "map1";

	resizeGui();
}


MapEditor::~MapEditor()
{
}

void MapEditor::resizeGui()
{
	Vec2f size(gui.getView().getSize());

	gui.findById("texturelist")->setPos(Vec2f(size.x - 100.f, size.y - 60.f));
	gui.findById("rightpanel")->setPos(Vec2f(size.x - 100.f, size.y/2.f));
	gui.findById("rightpanel")->setSize(Vec2f(200.f, size.y));
	gui.findById("sizeslider")->setPos(Vec2f(size.x - 100.f, size.y - 140.f));
	gui.findById("colorslider")->setPos(Vec2f(size.x - 100.f, size.y - 170.f));
	gui.findById("newbutton")->setPos(Vec2f(size.x - 100.f,30.f));
	gui.findById("savebutton")->setPos(Vec2f(size.x - 100.f, 70.f));
	gui.findById("loadbutton")->setPos(Vec2f(size.x - 100.f, 110.f));
	gui.findById("objectlist")->setPos(Vec2f(size.x - 100.f, size.y - 400.f));
}

void MapEditor::onObjectSelected(List * sender, ListItem item)
{
	tool = 1;
	objectAngle = 0.f;
}

void MapEditor::onTextureSelected(List * sender, ListItem item)
{
	if (item.id == "tex1")
		textureMode = 0;
	if (item.id == "tex2")
		textureMode = 1;
	if (item.id == "tex3")
		textureMode = 2;
}

void MapEditor::onNewButton(Button * sender, MouseDownEvent event)
{
	SimpleGuiWindow* window = new SimpleGuiWindow({
		SimpleWidget::TextLine(L"Are you sure?")
	}, SimpleGuiWindow::Style::OkCancel);

	window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {

		SimpleGuiWindow* window = new SimpleGuiWindow({
			SimpleWidget::TextLine(L"Creating new map"),
			SimpleWidget::EditBox("name",L"Name", L"map1"),
			SimpleWidget::EditBox("width",L"Width", L"3"),
			SimpleWidget::EditBox("height",L"Height", L"3"),
			SimpleWidget::EditBox("tilesize",L"Tilesize", L"6000")
		}, SimpleGuiWindow::Style::OkCancel);

		window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
			std::string folder = Util::wStrToStr(results["name"].editBox.text);
			mapName = folder;

			int w = Util::strToInt(results["width"].editBox.text);
			int h = Util::strToInt(results["height"].editBox.text);
			int tilesize = Util::strToInt(results["tilesize"].editBox.text);

			terrain.resetSize(Vec2i(w, h), tilesize);
			return true;
		});
		gui.add(window);

		return true;
	});
	gui.add(window);
}

void MapEditor::onSaveButton(Button * sender, MouseDownEvent event)
{
	SimpleGuiWindow* window = new SimpleGuiWindow({
		SimpleWidget::TextLine(L"Select map name"),
		SimpleWidget::EditBox("save",L"path", Util::strToWStr(mapName))
	}, SimpleGuiWindow::Style::OkCancel);

	window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
		std::string folder = Util::wStrToStr(results["save"].editBox.text);
		mapName = folder;
		terrain.save("maps/"+ folder + "/");
		objects.saveToFile("maps/" + folder + "/objects.json");
		return true;
	});
	gui.add(window);
}

void MapEditor::onLoadButton(Button * sender, MouseDownEvent event)
{
	SimpleGuiWindow* window = new SimpleGuiWindow({
		SimpleWidget::TextLine(L"Select map name to load"),
		SimpleWidget::EditBox("load",L"path", Util::strToWStr(mapName))
	}, SimpleGuiWindow::Style::OkCancel);

	window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
		std::string folder = Util::wStrToStr(results["load"].editBox.text);
		mapName = folder;
		terrain.load("maps/" + folder + "/");
		objects.loadFromFile("maps/" + folder + "/objects.json");
		return true;
	});
	gui.add(window);
}

float MapEditor::getRadius()
{
	float radius = 10.f + 190.f*((Slider*)gui.findById("sizeslider"))->getValue();
	return radius;
}

sf::Color MapEditor::getColor()
{
	float intensity = ((Slider*)gui.findById("colorslider"))->getValue();;
	sf::Color color(0, 0, 0, 50);
	if (textureMode == 0)
		color.r = 255 * intensity;
	if (textureMode == 1)
		color.g = 255 * intensity;
	if (textureMode == 2)
		color.b = 255 * intensity;
	return color;
}

void MapEditor::update(float dt)
{
	float cameraSpeed = 200.f*GameWindow::getZoom();
	if (Input::getKey(Input::LShift))
		cameraSpeed = 1000.f*GameWindow::getZoom();

	if (Input::getKey(Input::A))
		cameraPos.x -= dt*cameraSpeed;
	if (Input::getKey(Input::D))
		cameraPos.x += dt*cameraSpeed;
	if (Input::getKey(Input::W))
		cameraPos.y -= dt*cameraSpeed;
	if (Input::getKey(Input::S))
		cameraPos.y += dt*cameraSpeed;
	if (Input::getKey(Input::Q))
		objectAngle -= dt*100.f;
	if (Input::getKey(Input::E))
		objectAngle += dt*100.f;
	GameWindow::setCameraCenter(cameraPos);
}

void MapEditor::draw()
{
	terrain.draw();

	objects.draw();

	if (tool == 0)
	{
		sf::CircleShape shape;
		shape.setPosition(Input::getWorldMousePos().toSFMLVec());
		shape.setRadius(getRadius());
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		shape.setFillColor(sf::Color(0, 0, 0, 0));
		shape.setOutlineColor(getColor());
		shape.setOutlineThickness(2.f);
		GameWindow::getInternalHandle().draw(shape);
	}
	else if (tool == 1)
	{
		ListItem* selected = ((List*)gui.findById("objectlist"))->getSelected();
		if (selected)
		{
			StaticObject object = ObjectManager::getObject(selected->id);
			object.setPos(Input::getWorldMousePos());
			object.setSize(Vec2f(1.f, 1.f));
			object.setAng(objectAngle);
			object.draw();
		}
	}
		


	gui.draw();
}

void MapEditor::handleEvent(sf::Event event)
{
	bool handled = gui.handleEvent(event);

	if (event.type == sf::Event::Resized)
		resizeGui();

	if (handled)
		return;
	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
			GameWindow::zoom(0.9f);
		else
			if (GameWindow::getZoom() < 100.f)
				GameWindow::zoom(1.1f);
	}
	if (event.type == sf::Event::MouseMoved && tool == 0)
	{
		if (Input::getMouse(Input::MouseLeft))
		{
			Vec2f pos = Input::getWorldMousePos();
			sf::Color color = getColor();
			float radius = getRadius();

			if(textureMode >= 0)
				terrain.drawOnMap(pos, radius, color);
		}
	}
	if (tool == 1)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Button::Right)
			{
				tool = 0;
			}
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				ListItem* selected = ((List*)gui.findById("objectlist"))->getSelected();
				if (selected)
				{
					StaticObject object = ObjectManager::getObject(selected->id);
					object.setPos(Input::getWorldMousePos());
					object.setSize(Vec2f(1.f,1.f));
					object.setAng(objectAngle);
					objects.addObject(object);
				}
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Delete)
			{
				objects.remoteObjectAt(Input::getWorldMousePos(), 50.f);
			}
		}
	}
}
