/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by creepy,
*/
#ifndef _Room_H_
#define _Room_H_

#include "../../GameEngine/GameEngine.hpp"

class Room {
	public:
	Room(const std::string &,
		const std::shared_ptr<boost::asio::ip::udp::socket> &
	);

	void handleReceive(const boost::property_tree::ptree &);

	const std::string &getName() const;

	std::size_t getNumberPlayer();

	Entity &createPlayer(const boost::asio::ip::udp::endpoint &);

	void join(const Entity &);

	void quit(const boost::property_tree::ptree &);

	void run();

	void startGame(const boost::property_tree::ptree &);

	void finishGame();

	void destroy(int);

	std::string  generateNickname(std::size_t);

	bool isRunning() const;

	void setRunning(bool _running);

	void movePlayer(const boost::property_tree::ptree &);

	private:
	Manager _manager;
	std::string _name;
	std::shared_ptr<boost::asio::ip::udp::socket> _socket;
	int _uuid;
	bool _running = false;
	std::map<std::string, std::function<void(const boost::property_tree::ptree &)>> _command;
	std::thread *_thread;
};

#endif // _Room_H_
