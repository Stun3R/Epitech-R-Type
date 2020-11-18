/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef SHOME_HPP
#define SHOME_HPP

#include "../State.hpp"

class SHome : public State {
	public:
	enum Widget {
		Background,
		BtnCreate,
		BtnJoin,
		BtnQuit
	};

	explicit SHome(Client *);

	void spriteFactory(Widget);

	void input() override;

	void draw() override;

	void handleReceive(const boost::property_tree::ptree &) override;

	private:
	Client *_context;
	Window *_window;
	std::map<Widget, sf::Texture> _texture;
	std::map<Widget, sf::Sprite> _sprite;
};

#endif //SHOME_HPP
