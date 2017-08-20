#include "Input.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "GameWindow.h"

bool Input::pressedButtons[Input::KeyCount];
bool Input::pressedButtonsSaved[Input::KeyCount];
bool Input::mousePressedButtons[Input::ButtonCount];
bool Input::mousePressedButtonsSaved[Input::ButtonCount];
Vec2f Input::delta;
Vec2f Input::oldMousePos;

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
		pressedButtonsSaved[i] = pressedButtons[i];

		pressedButtons[i] = getKey((Key)i);
	}

	for (int i = 0; i<Input::ButtonCount; i++)
	{
		mousePressedButtonsSaved[i] = mousePressedButtons[i];

		mousePressedButtons[i] = getMouse((MouseButton)i);
	}

	Vec2f newpos = getWorldMousePos();

	delta = Vec2f::sub( newpos, oldMousePos );

	oldMousePos = newpos;

}

bool Input::getMouse(MouseButton b)
{
	return sf::Mouse::isButtonPressed((sf::Mouse::Button)b);
}

bool Input::getMouseDown(MouseButton b)
{
	return !mousePressedButtonsSaved[b] && mousePressedButtons[b];
	//return getMouse(b) && !mousePressedButtons[b];
}

bool Input::getMouseUp(MouseButton b)
{
	return mousePressedButtonsSaved[b] && !mousePressedButtons[b];
	//return !getMouse(b) && mousePressedButtons[b];
}

bool Input::getKey(Key key)
{
	if (!GameWindow::isFocused())
	{
		return false;
	}
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

bool Input::getKeyDown(Key key)
{
	return !pressedButtonsSaved[key] && pressedButtons[key];
	//return getKey(key) && !pressedButtons[key];
}

bool Input::getKeyUp(Key key)
{
	return pressedButtonsSaved[key] && !pressedButtons[key];
	//return !getKey(key) && pressedButtons[key];
}

Vec2i Input::getMousePos()
{
	return GameWindow::getMousePos();
}

Vec2f Input::getWorldMousePos()
{
	return Vec2f(GameWindow::getInternalHandle().mapPixelToCoords(GameWindow::getMousePos().toSFMLVec()));
}

Vec2f Input::getWorldMouseDelta()
{
	return delta;
}
