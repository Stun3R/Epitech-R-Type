/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef STATE_HPP
#define STATE_HPP

#include "../../GameEngine/Library.hpp"

class Client;

class Window;

class State {
	public:
	virtual void input() {};

	virtual void draw() {};

	virtual void handleReceive(const boost::property_tree::ptree &) {};

	virtual void sendServer(const boost::property_tree::ptree &) {};

	protected:
	boost::asio::ip::udp::endpoint _endpoint;
	std::shared_ptr<boost::asio::ip::udp::socket> _socket;
	std::map<std::string, std::function<void(const boost::property_tree::ptree &)>> _command;
	int _id = -1;
	std::string _roomName;
};

#endif //STATE_HPP
