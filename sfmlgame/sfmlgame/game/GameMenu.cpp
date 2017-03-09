#include "GameMenu.h"
#include "Util.h"
#include "SimpleGuiWindow.h"
#include "Game.h"
#include "Application.h"
#include "AnimationEditor.h"
#include "MapEditor.h"

GameMenu::GameMenu()
{
	{
		Button* button1 = new Button();
		button1->setSize(Vec2f(150.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Выйти");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&GameMenu::onQuitButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "quit");
	}
	{
		Button* button1 = new Button();
		button1->setSize(Vec2f(150.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Создать игру");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&GameMenu::onHostButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "host");
	}
	{
		Button* button1 = new Button();
		button1->setSize(Vec2f(150.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Присоединиться");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&GameMenu::onConnectButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "connect");
	}
	{
		Button* button1 = new Button();
		button1->setSize(Vec2f(150.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Редактор анимаций");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&GameMenu::onAnimButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "anims");
	}
	{
		Button* button1 = new Button();
		button1->setSize(Vec2f(150.f, 30.f));
		button1->setTextSize(12u);
		button1->setTexture("button");
		button1->setText(L"Редактор карт");
		button1->setMult(0.3f);
		button1->OnClick(std::bind(&GameMenu::onMapButton, this, std::placeholders::_1, std::placeholders::_2));
		gui.add(button1, "map");
	}

	resizeGui();
}

void GameMenu::resizeGui()
{
	Vec2f size(gui.getView().getSize());
	int count = 4;
	int i = 0;
	float w = 150.f;

	gui.findById("host")->setPos(Vec2f(size.x/2.f, size.y/2.f - w/2.f + w*((float)i/count)));
	i++;
	gui.findById("connect")->setPos(Vec2f(size.x / 2.f, size.y / 2.f - w / 2.f + w*((float)i / count)));
	i++;
	gui.findById("anims")->setPos(Vec2f(size.x / 2.f, size.y / 2.f - w / 2.f + w*((float)i / count)));
	i++;
	gui.findById("map")->setPos(Vec2f(size.x / 2.f, size.y / 2.f - w / 2.f + w*((float)i / count)));
	i++;
	gui.findById("quit")->setPos(Vec2f(size.x / 2.f, size.y / 2.f - w / 2.f + w*((float)i / count)));
	i++;
}

void GameMenu::onQuitButton(Button * sender, MouseDownEvent event)
{
	finish();
}

void GameMenu::onConnectButton(Button * sender, MouseDownEvent event)
{
	SimpleGuiWindow* window = new SimpleGuiWindow({
		SimpleWidget::TextLine(L"Присоединение к игре"),
		SimpleWidget::EditBox("ip",L"ip", L"127.0.0.1")
	}, SimpleGuiWindow::Style::OkCancel);

	window->OnOk([&](std::unordered_map<std::string, SimpleGuiWindow::Result>& results) {
		std::string ip = Util::wStrToStr(results["load"].editBox.text);

		pushState(new Game(ip));
		return true;
	});
	gui.add(window);
}

void GameMenu::onHostButton(Button * sender, MouseDownEvent event)
{
	app->startServer();
	pushState(new Game());
}

void GameMenu::onAnimButton(Button * sender, MouseDownEvent event)
{
	pushState(new AnimationEditor());
}

void GameMenu::onMapButton(Button * sender, MouseDownEvent event)
{
	pushState(new MapEditor());
}

GameMenu::~GameMenu()
{
}

void GameMenu::update(float dt)
{
}

void GameMenu::draw()
{
	gui.draw();
}

void GameMenu::handleEvent(sf::Event event)
{
	bool handled = gui.handleEvent(event);

	if (event.type == sf::Event::Resized)
		resizeGui();
}


