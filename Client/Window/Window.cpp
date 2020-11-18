/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "Window.hpp"

void Window::init()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	_window.create(sf::VideoMode(1280, 720), "R-TYPE", sf::Style::Titlebar);
	_window.setPosition(sf::Vector2i((desktop.width / 2) - (1280 / 2), (desktop.height / 2) - (720 / 2)));
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(120);
	_font.loadFromFile("assets/UI/Fonts/KoHo-Regular.ttf");
	_focus = true;
}

sf::RenderWindow &Window::getWindow()
{
	return _window;
}

void Window::manageEvent()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::LostFocus:
			_focus = false;
			break;
		case sf::Event::GainedFocus:
			_focus = true;
			break;
		}
	}
}

void Window::update()
{
	manageEvent();
	_window.display();
}

void Window::clear()
{
	_window.clear();
}

void Window::close()
{
	_window.close();
}

bool Window::isOpen()
{
	return _window.isOpen();
}

bool Window::isFocus()
{
	return _focus;
}

void Window::setFocus(bool mFocus)
{
	_focus = mFocus;
}

const sf::Font &Window::getFont() const
{
	return _font;
}

void Window::setFont(const std::string &mPath)
{
	_font.loadFromFile("assets/UI/Fonts/KoHo-Regular.ttf");
}
