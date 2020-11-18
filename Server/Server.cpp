/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "Server.hpp"

Server::Server()
	: _ioservice(), _socket(std::make_shared<boost::asio::ip::udp::socket>(_ioservice,
	boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 4242)))
{
	_command["CREATE"] = std::bind(&Server::createRoom, this, std::placeholders::_1);
	_command["JOIN"] = std::bind(&Server::joinRoom, this, std::placeholders::_1);
	_command["LIST"] = std::bind(&Server::listRoom, this, std::placeholders::_1);
	_command["DESTROY"] = std::bind(&Server::destroyRoom, this, std::placeholders::_1);
	_command["ROOM"] = std::bind(&Server::roomReceive, this, std::placeholders::_1);
}

Server::~Server()
{
	_ioservice.stop();
}

void Server::run()
{
	startReceive();
	while (true) {
		refresh();
		_ioservice.poll();
	}
}

void Server::refresh()
{
	for (auto &room : _rooms) {
		if (room->getNumberPlayer() == 0) {
			auto it = std::find(_rooms.begin(), _rooms.end(), room);
			room->finishGame();
			_rooms.erase(it);
		}
	}
}

void Server::startReceive()
{
	_socket->async_receive_from(boost::asio::buffer(_buffer), _endpoint,
		boost::bind(&Server::handleReceive, this, boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void Server::handleReceive(const boost::system::error_code &error, std::size_t bytes
)
{
	if (!error || error == boost::asio::error::message_size) {

		std::string receive_json = std::string(_buffer.begin(), _buffer.begin() + bytes);
		boost::property_tree::ptree root;
		std::stringstream ss;
		ss << receive_json;

		try {
			boost::property_tree::read_json(ss, root);
		} catch (std::exception &e) {
			std::cout << "Error: " << e.what() << std::endl;
		}

		std::string type = root.get<std::string>("TYPE");
		std::map<std::string, std::function<void(const boost::property_tree::ptree &)>>::iterator it;
		for (it = _command.begin(); it != _command.end(); it++)
			if (it->first == type)
				it->second(root);
		startReceive();
	}
}

void Server::handleSend(std::shared_ptr<std::string> message, const boost::system::error_code &error, std::size_t bytes
)
{
	if (!error) {
		std::cout << *message << " was sent" << std::endl;
	} else {
		std::cout << error.message() << std::endl;
	}
}

bool Server::hasRoom(const std::string &mName)
{
	std::set<Room *>::iterator it;

	for (it = _rooms.begin(); it != _rooms.end(); it++) {
		if (mName == (*it)->getName())
			return true;
	}
	return false;
}

Room *Server::getRoomsByName(const std::string &mName) const
{
	std::set<Room *>::iterator it;

	for (it = _rooms.begin(); it != _rooms.end(); it++) {
		if (mName == (*it)->getName())
			return (*it);
	}
	return nullptr;
}

void Server::createRoom(const boost::property_tree::ptree &tree)
{
	boost::property_tree::ptree root;
	std::string mName = tree.get<std::string>("ROOM");

	if (hasRoom(mName)) {
		root.put("TYPE", "FAILED");
		std::ostringstream buf;
		write_json(buf, root, false);
		std::string data = buf.str();

		_socket->send_to(boost::asio::buffer(data), _endpoint);
	} else {
		_rooms.insert(new Room(mName, _socket));
		auto room = getRoomsByName(mName);
		room->createPlayer(_endpoint);
	}
}

void Server::joinRoom(const boost::property_tree::ptree &tree)
{
	std::string mName = tree.get<std::string>("ROOM");
	auto room = getRoomsByName(mName);
	if (room != nullptr) {
		auto &e = room->createPlayer(_endpoint);
		room->join(e);
	}
}

void Server::listRoom(const boost::property_tree::ptree &tree)
{
	boost::property_tree::ptree root;
	boost::property_tree::ptree node;

	root.put("TYPE", "LIST");
	for (auto &room : _rooms) {
		if (room->getNumberPlayer() < 4 && !room->isRunning()) {
			node.put(room->getName(), room->getNumberPlayer());
		}
	}
	root.add_child("ROOMS", node);
	std::ostringstream buf;
	write_json(buf, root, false);
	std::string data = buf.str();
	_socket->send_to(boost::asio::buffer(data), _endpoint);
}

void Server::destroyRoom(const boost::property_tree::ptree &mRoot)
{
	auto room = getRoomsByName(mRoot.get<std::string>("ROOM"));
	room->destroy(mRoot.get<int>("ID"));
	auto it = std::find(_rooms.begin(), _rooms.end(), room);
	_rooms.erase(it);
}

void Server::roomReceive(const boost::property_tree::ptree &mRoot)
{
	auto room = getRoomsByName(mRoot.get<std::string>("ROOM"));
	if (room != nullptr)
		room->handleReceive(mRoot);
}