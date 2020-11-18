#include <utility>

/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "DeliverComponent.hpp"

DeliverComponent::DeliverComponent(const std::shared_ptr<boost::asio::ip::udp::socket> &mSocket,
	const boost::asio::ip::udp::endpoint &mEndpoint
) : _socket(mSocket), _endpoint(mEndpoint)
{
}

void DeliverComponent::deliver(const std::string &toDeliver)
{
	bool inProgress = !_queue.empty();
	_queue.push_back(toDeliver);
	if (!inProgress) {
		_socket->async_send_to(boost::asio::buffer(_queue.front()), _endpoint,
			boost::bind(&DeliverComponent::handleSend, this, _queue.front(),
				boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
}

void DeliverComponent::handleSend(const std::string &toDeliver, const boost::system::error_code &error,
	std::size_t bytes
)
{
	if (!error) {
		if (!_queue.empty()) {
			_queue.pop_front();
			if (!_queue.empty()) {
				_socket->async_send_to(boost::asio::buffer(_queue.front()), _endpoint,
					boost::bind(&DeliverComponent::handleSend, this, _queue.front(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			}
		}
	}
}
