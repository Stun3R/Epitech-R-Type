/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by creepy,
*/

#include "Room.hpp"

Room::Room(const std::string &mName, const std::shared_ptr<boost::asio::ip::udp::socket> &mSocket
) : _name(mName), _socket(mSocket)
{
	_command["QUIT"] = std::bind(&Room::quit, this, std::placeholders::_1);
	_command["MOVE"] = std::bind(&Room::movePlayer, this, std::placeholders::_1);
	_command["READY"] = std::bind(&Room::startGame, this, std::placeholders::_1);
}

void Room::handleReceive(const boost::property_tree::ptree &mRoot)
{
	std::string action = mRoot.get<std::string>("ACTION");
	std::map<std::string, std::function<void(const boost::property_tree::ptree &)>>::iterator it;
	for (it = _command.begin(); it != _command.end(); it++)
		if (it->first == action)
			it->second(mRoot);
}

void Room::join(const Entity &mEntity)
{
	for (auto &e : _manager.getEntitiesByGroup(GameGroup::Player)) {
		if (e->getId() != mEntity.getId()) {
			boost::property_tree::ptree root;
			root.put("ID", mEntity.getId());
			root.put("NAME", mEntity.getComponent<NicknameComponent>().getNickname());
			root.put("X", 0);
			root.put("Y", 0);
			root.put("TYPE", "NEWCOOP");

			std::stringstream ss;
			boost::property_tree::write_json(ss, root);
			e->getComponent<DeliverComponent>().deliver(ss.str());
		}
	}

	for (auto &e : _manager.getEntitiesByGroup(GameGroup::Player)) {
		if (e->getId() != mEntity.getId()) {
			boost::property_tree::ptree root;
			root.put("ID", e->getId());
			root.put("NAME", e->getComponent<NicknameComponent>().getNickname());
			root.put("X", e->getComponent<PositionComponent>().x());
			root.put("Y", e->getComponent<PositionComponent>().y());
			root.put("TYPE", "NEWCOOP");

			std::stringstream ss;
			boost::property_tree::write_json(ss, root);
			mEntity.getComponent<DeliverComponent>().deliver(ss.str());
		}
	}
}

void Room::quit(const boost::property_tree::ptree &mRoot)
{
	boost::property_tree::ptree root;
	auto player = _manager.getPlayerById(mRoot.get<int>("ID"));
	if (player != nullptr) {
		player->destroy();
		_manager.refresh();
		root.put("TYPE", "DESTROY");
		root.put("ID", player->getId());
		std::stringstream ss;
		boost::property_tree::write_json(ss, root);
		for (auto &p : _manager.getEntitiesByGroup(GameGroup::Player))
			p->getComponent<DeliverComponent>().deliver(ss.str());
	}
}

void Room::run()
{
	_running = true;
	while (_running) {
		// game logic
	}
}

void Room::movePlayer(const boost::property_tree::ptree &mRoot)
{
	boost::property_tree::ptree root;
	auto player = _manager.getPlayerById(mRoot.get<int>("ID"));
	auto pos = player->getComponent<PositionComponent>().getPosition();
	auto speed = player->getComponent<SpeedComponent>().getSpeed();
	std::string dir = mRoot.get<std::string>("DIR");
	if (dir == "UP" && pos.y > (0 + speed))
		player->getComponent<PositionComponent>().move(0, -speed);
	else if (dir == "DOWN" && pos.y < (720 - speed))
		player->getComponent<PositionComponent>().move(0, speed);
	else if (dir == "LEFT" && pos.x > (0 + speed))
		player->getComponent<PositionComponent>().move(-speed, 0);
	else if (dir == "RIGHT" && pos.x < (1280 - speed))
		player->getComponent<PositionComponent>().move(speed, 0);

	root.put("TYPE", "MOVE");
	root.put("ID", player->getId());
	root.put("X", player->getComponent<PositionComponent>().getPosition().x);
	root.put("Y", player->getComponent<PositionComponent>().getPosition().y);
	std::stringstream ss;
	boost::property_tree::write_json(ss, root);

	for (auto &e : _manager.getEntitiesByGroup(GameGroup::Player))
		e->getComponent<DeliverComponent>().deliver(ss.str());
}

const std::string &Room::getName() const
{
	return _name;
}

std::size_t Room::getNumberPlayer()
{
	return _manager.getEntitiesByGroup(GameGroup::Player).size();
}

Entity &Room::createPlayer(const boost::asio::ip::udp::endpoint &mEndpoint)
{
	boost::property_tree::ptree root;
	std::stringstream ss;
	auto &entity = _manager.addEntity(_uuid++);

	entity.addComponent<PositionComponent>(sf::Vector2f(0, 0));
	entity.addComponent<HealthComponent>();
	entity.addComponent<PowerComponent>();
	entity.addComponent<SpeedComponent>(Speed::Medium);
	entity.addComponent<NicknameComponent>(generateNickname(getNumberPlayer() + 1));
	entity.addComponent<ScoreComponent>();
	entity.addComponent<DeliverComponent>(_socket, mEndpoint);
	entity.addGroup(GameGroup::Player);

	root.put("ID", entity.getId());
	root.put("NAME", entity.getComponent<NicknameComponent>().getNickname());
	root.put("X", 0);
	root.put("Y", 0);
	root.put("TYPE", "NEWPLAYER");
	boost::property_tree::write_json(ss, root);
	entity.getComponent<DeliverComponent>().deliver(ss.str());

	return entity;
}

void Room::destroy(int mId)
{
	boost::property_tree::ptree root;
	root.put("TYPE", "LEAVE");
	std::stringstream ss;
	boost::property_tree::write_json(ss, root);

	for (auto &e : _manager.getEntitiesByGroup(GameGroup::Player)) {
		if (e->getId() != mId)
			e->getComponent<DeliverComponent>().deliver(ss.str());
	}
}

void Room::startGame(const boost::property_tree::ptree &mRoot)
{
	boost::property_tree::ptree root;
	root.put("TYPE", "LAUNCH");
	std::stringstream ss;
	boost::property_tree::write_json(ss, root);

	for (auto &e : _manager.getEntitiesByGroup(GameGroup::Player)) {
		e->getComponent<DeliverComponent>().deliver(ss.str());
	}
	_thread = new std::thread(&Room::run, this);
}

void Room::finishGame()
{
	_running = false;
	_thread->join();
}

std::string Room::generateNickname(std::size_t mNumber)
{
	switch (mNumber) {
	case 1:
		return "Blue";
	case 2:
		return "Red";
	case 3:
		return "Yellow";
	case 4:
		return "Green";
	}
	return NULL;
}

bool Room::isRunning() const
{
	return _running;
}

void Room::setRunning(bool mRunning)
{
	_running = mRunning;
}


