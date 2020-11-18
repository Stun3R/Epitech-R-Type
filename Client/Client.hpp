/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../GameEngine/Library.hpp"
#include "Window/Window.hpp"
#include "State/State.hpp"
#include "State/SHome/SHome.hpp"
#include "State/SGame/SGame.hpp"
#include "State/SCreate/SCreate.hpp"
#include "State/SJoin/SJoin.hpp"

class Client {
	public:
	Client();

	~Client();

	void run();

	void init(const std::string &, const std::string &);

	void setState(State *);

	Window &getWindow();

	std::shared_ptr<boost::asio::ip::udp::socket> getSocket();

	boost::asio::ip::udp::endpoint getEndpoint();

	private:

	void startReceive();

	void handleReceive(const boost::system::error_code &, std::size_t);

	void handleSend(std::shared_ptr<std::string>,
		const boost::system::error_code &, std::size_t
	);

	const double calculateDeltaTime(sf::Clock &, sf::Time &);

	boost::asio::io_service _ioservice;
	boost::asio::ip::udp::endpoint _endpoint;
	std::shared_ptr<boost::asio::ip::udp::socket> _socket;
	std::array<char, 256> _buffer;
	Window _window;
	State *_state;
};

#endif //CLIENT_HPP
