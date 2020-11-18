/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef SJOIN_HPP
#define SJOIN_HPP

#include "../../../GameEngine/GameEngine.hpp"
#include "../State.hpp"

class SJoin : public State {
	public:
	explicit SJoin(Client *);

	void input() override;

	void draw() override;

	void handleReceive(const boost::property_tree::ptree &) override;

	void sendServer(const boost::property_tree::ptree &);

	private:

	void feedList(const boost::property_tree::ptree &);

	void createPlayer(const boost::property_tree::ptree &);

	void destroyEntity(const boost::property_tree::ptree &);

	void leaveRoom(const boost::property_tree::ptree &);

	void createCoop(const boost::property_tree::ptree &);

	void launch(const boost::property_tree::ptree &);

	sf::Text textFactory(const std::string &, int);

	Client *_context;
	Window *_window;
	Manager _manager;
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Text _waitText;
	bool _click = false;
	bool _wait = false;
	std::vector<sf::Text> _viewList;
};

#endif //SJOIN_HPP
