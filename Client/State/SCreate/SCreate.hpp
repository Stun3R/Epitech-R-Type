/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef SCREATE_HPP
#define SCREATE_HPP

#include "../../../GameEngine/GameEngine.hpp"
#include "../State.hpp"

class SCreate : public State {
	public:
	explicit SCreate(Client *);

	void input() override;

	void draw() override;

	void handleReceive(const boost::property_tree::ptree &) override;

	void sendServer(const boost::property_tree::ptree &);

	void failed(const boost::property_tree::ptree &);

	void createPlayer(const boost::property_tree::ptree &);

	void destroyEntity(const boost::property_tree::ptree &);

	void createCoop(const boost::property_tree::ptree &);

	void launch(const boost::property_tree::ptree &);

	private:
	Client *_context;
	Window *_window;
	Manager _manager;
	bool _send = false;
	sf::Texture _bgTexture;
	sf::Texture _stTexture;
	sf::Sprite _bgSprite;
	sf::Sprite _stSprite;
	sf::Text _name;
};

#endif //SCREATE_HPP
