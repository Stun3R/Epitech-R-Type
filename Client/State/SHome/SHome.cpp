/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "SHome.hpp"
#include "../../Client.hpp"

SHome::SHome(Client *mContext) : _context(mContext), _window(&mContext->getWindow())
{
	_endpoint = _context->getEndpoint();
	_socket = _context->getSocket();
	sf::Vector2u windowSize = _context->getWindow().getWindow().getSize();

	_texture[Widget::Background].loadFromFile("assets/UI/Background/Background.png");
	_texture[Widget::BtnQuit].loadFromFile("assets/UI/Button/Quit.png");
	_texture[Widget::BtnCreate].loadFromFile("assets/UI/Button/Create.png");
	_texture[Widget::BtnJoin].loadFromFile("assets/UI/Button/Join.png");

	for (int WidgetInt = Background; WidgetInt != BtnQuit + 1; WidgetInt++)
		spriteFactory(static_cast<Widget>(WidgetInt));
}

void SHome::draw()
{
	for (auto const &s: _sprite) {
		_window->getWindow().draw(s.second);
	}
}

bool checkMouseClick(sf::Sprite &mSprite, sf::Vector2f mousePosition)
{
	return mSprite.getGlobalBounds().contains(mousePosition);
}

void SHome::input()
{
	sf::Vector2i mouse;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		mouse = sf::Mouse::getPosition(_window->getWindow());
		if (checkMouseClick(_sprite[BtnQuit], sf::Vector2f(mouse)))
			_window->close();
		if (checkMouseClick(_sprite[BtnCreate], sf::Vector2f(mouse)))
			_context->setState(new SCreate(_context));
		if (checkMouseClick(_sprite[BtnJoin], sf::Vector2f(mouse)))
			_context->setState(new SJoin(_context));
	}
}

void SHome::handleReceive(const boost::property_tree::ptree &mRoot)
{
}

void SHome::spriteFactory(Widget mWidget)
{
	sf::FloatRect mSize;
	sf::Vector2u mWindowSize = _context->getWindow().getWindow().getSize();
	float mPadding = 0;

	switch (mWidget) {
	case Background:
		_sprite[mWidget].setTexture(_texture[mWidget]);
		break;
	case BtnCreate:
		_sprite[mWidget].setTexture(_texture[mWidget]);
		mSize = _sprite[mWidget].getGlobalBounds();
		_sprite[mWidget].setPosition(0, (mWindowSize.y / 2) - mSize.height - 100);
		break;
	case BtnJoin:
		_sprite[mWidget].setTexture(_texture[mWidget]);
		mSize = _sprite[mWidget].getGlobalBounds();
		_sprite[mWidget].setPosition(0, (mWindowSize.y / 2) - mSize.height);
		break;
	case BtnQuit:
		_sprite[mWidget].setTexture(_texture[mWidget]);
		mSize = _sprite[mWidget].getGlobalBounds();
		_sprite[mWidget].setPosition(0, (mWindowSize.y / 2) - mSize.height + 100);
		break;
	}
}
