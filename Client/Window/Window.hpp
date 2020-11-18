/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../../GameEngine/Library.hpp"

class Window {
	public:
	sf::RenderWindow &getWindow();

	void init();

	void update();

	void clear();

	void close();

	void manageEvent();

	bool isOpen();

	bool isFocus();

	void setFocus(bool);

	const sf::Font &getFont() const;

	void setFont(const std::string &);

	private:
	sf::RenderWindow _window;
	sf::Font _font;
	bool _focus;
};

#endif //WINDOW_HPP
