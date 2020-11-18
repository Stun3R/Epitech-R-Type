/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef SGAME_HPP
#define SGAME_HPP

#include "../../../GameEngine/GameEngine.hpp"
#include "../State.hpp"

class SGame : public State {
	public:
	explicit SGame(Client *, Manager , int, const std::string &);

	void input() override;

	void draw() override;

	void handleReceive(const boost::property_tree::ptree &) override;

	void sendServer(const boost::property_tree::ptree &) override;

	void sendMovement(const std::string &);

	void destroyEntity(const boost::property_tree::ptree &);

	void moveEntity(const boost::property_tree::ptree &);

	private:
	Client *_context;
	Window *_window;
	Manager _manager;
	std::string _roomName;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

#endif //SGAME_HPP
