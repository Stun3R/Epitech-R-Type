/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef DELIVERCOMPONENT_HPP
#define DELIVERCOMPONENT_HPP

#include "../Component.hpp"
#include "../../Library.hpp"

class DeliverComponent : public Component {
	public:
	DeliverComponent(const std::shared_ptr<boost::asio::ip::udp::socket> &, const boost::asio::ip::udp::endpoint &);

	void deliver(const std::string &);

	void handleSend(const std::string &, const boost::system::error_code &, std::size_t);

	private:
	std::shared_ptr<boost::asio::ip::udp::socket> _socket;
	boost::asio::ip::udp::endpoint _endpoint;
	std::deque<std::string> _queue;
};

#endif //DELIVERCOMPONENT_HPP
