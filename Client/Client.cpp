/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "Client.hpp"

Client::Client() : _socket(std::make_shared<boost::asio::ip::udp::socket>(_ioservice))
{
}

Client::~Client()
{
	_ioservice.stop();
}

void Client::run()
{
	_window.init();
	_state = new SHome(this);
	startReceive();
	while (_window.isOpen()) {
		_window.clear();
		if (_window.isFocus())
			_state->input();
		_state->draw();
		_window.update();
		_ioservice.poll();
	}
}

void Client::init(const std::string &host, const std::string &port)
{
	try {
		boost::asio::ip::udp::resolver resolver(_ioservice);
		boost::asio::ip::udp::resolver::query query(host, port);
		_endpoint = *resolver.resolve(query);

		_socket->open(boost::asio::ip::udp::v4());
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(84);
	}
}

void Client::startReceive()
{
	boost::asio::ip::udp::endpoint sender_endpoint;
	_socket->async_receive_from(boost::asio::buffer(_buffer), sender_endpoint,
		boost::bind(&Client::handleReceive, this, boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void Client::handleReceive(const boost::system::error_code &error, std::size_t bytes)
{
	if (!error || error == boost::asio::error::message_size) {
		std::string receive_json = std::string(_buffer.begin(), _buffer.begin() + bytes);
		boost::property_tree::ptree root;
		std::stringstream ss;
		ss << receive_json;

		try {
			read_json(ss, root);
		} catch (std::exception &e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
		_state->handleReceive(root);
		startReceive();
	} else {
		std::cout << error.message() << std::endl;
	}
}

void Client::handleSend(std::shared_ptr<std::string> message, const boost::system::error_code &error, std::size_t bytes
)
{
}

void Client::setState(State *state)
{
	_state = state;
}

Window &Client::getWindow()
{
	return _window;
}

std::shared_ptr<boost::asio::ip::udp::socket> Client::getSocket()
{
	return _socket;
}

boost::asio::ip::udp::endpoint Client::getEndpoint()
{
	return _endpoint;
}


