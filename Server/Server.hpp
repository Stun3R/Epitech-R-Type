/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Room/Room.hpp"

class Server {
	public:
	Server();

	~Server();

	void run();

	void startReceive();

	void refresh();

	private:

	void handleReceive(const boost::system::error_code &, std::size_t);

	void handleSend(std::shared_ptr<std::string>, const boost::system::error_code &, std::size_t);

	bool hasRoom(const std::string &);

	Room *getRoomsByName(const std::string &) const;

	void createRoom(const boost::property_tree::ptree &);

	void joinRoom(const boost::property_tree::ptree &);

	void destroyRoom(const boost::property_tree::ptree &);

	void listRoom(const boost::property_tree::ptree &);

	void roomReceive(const boost::property_tree::ptree &);

	std::set<Room *> _rooms;
	boost::asio::io_service _ioservice;
	std::shared_ptr<boost::asio::ip::udp::socket> _socket;
	boost::asio::ip::udp::endpoint _endpoint;
	std::array<char, 128> _buffer;
	std::map<std::string, std::function<void(const boost::property_tree::ptree &)>> _command;
};

#endif //SERVER_HPP
