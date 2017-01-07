#include "Input.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "GameWindow.h"

bool Input::pressedButtons[Input::KeyCount];
bool Input::mousePressedButtons[Input::ButtonCount];

Input::Input()
{
}

Input::~Input()
{
}

void Input::update()
{
	for (int i = 0; i<Input::KeyCount; i++)
	{
		pressedButtons[i] = getKey((Key)i);
	}

	for (int i = 0; i<Input::ButtonCount; i++)
	{
		mousePressedButtons[i] = getMouse((MouseButton)i);
	}
}

bool Input::getMouse(MouseButton b)
{
	return sf::Mouse::isButtonPressed((sf::Mouse::Button)b);
}

bool Input::getMouseDown(MouseButton b)
{
	return getMouse(b) && !mousePressedButtons[b];
}

bool Input::getMouseUp(MouseButton b)
{
	return !getMouse(b) && mousePressedButtons[b];
}

bool Input::getKey(Key key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

bool Input::getKeyDown(Key key)
{
	return getKey(key) && !pressedButtons[key];
}

bool Input::getKeyUp(Key key)
{
	return !getKey(key) && pressedButtons[key];
}

Vec2i Input::getMousePos()
{
	return GameWindow::getMousePos();
}