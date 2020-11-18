/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "SGame.hpp"
#include "../../Client.hpp"

SGame::SGame(Client *mContext, Manager mManager, int mId, const std::string &mRoomName) : _context(mContext),
	_window(&mContext->getWindow()), _manager(std::move(mManager)), _roomName(mRoomName)
{
	_id = mId;
	_socket = _context->getSocket();
	_endpoint = _context->getEndpoint();
	_texture.loadFromFile("assets/UI/Background/Game_bg.png");
	_sprite.setTexture(_texture);

	_command["DESTROY"] = std::bind(&SGame::destroyEntity, this, std::placeholders::_1);
	_command["MOVE"] = std::bind(&SGame::moveEntity, this, std::placeholders::_1);
}

void SGame::input()
{
	boost::property_tree::ptree root;
	auto player = _manager.getPlayerById(_id);

	player->getComponent<GraphicsComponent>().getSprite().getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		root.put("TYPE", "ROOM");
		root.put("ACTION", "QUIT");
		root.put("ID", _id);
		root.put("ROOM", _roomName);
		sendServer(root);
		_context->setState(new SHome(_context));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		sendMovement("UP");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		sendMovement("DOWN");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		sendMovement("LEFT");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		sendMovement("RIGHT");
}

void SGame::handleReceive(const boost::property_tree::ptree &mRoot)
{
	std::string type = mRoot.get<std::string>("TYPE");
	std::map<std::string, std::function<void(const boost::property_tree::ptree &)>>::iterator it;
	for (it = _command.begin(); it != _command.end(); it++)
		if (it->first == type)
			it->second(mRoot);
}

void SGame::draw()
{
	_window->getWindow().draw(_sprite);
	auto &entities = _manager.getEntities();
	for (auto &e : entities) {
		_window->getWindow().draw(e->getComponent<GraphicsComponent>().getSprite());
	}
}

void SGame::sendMovement(const std::string &mDIR)
{
	boost::property_tree::ptree root;

	root.put("TYPE", "ROOM");
	root.put("ACTION", "MOVE");
	root.put("DIR", mDIR);
	root.put("ID", _id);
	root.put("ROOM", _roomName);
	sendServer(root);
}

void SGame::sendServer(const boost::property_tree::ptree &mRoot)
{
	std::ostringstream buf;
	write_json(buf, mRoot, false);
	std::string data = buf.str();
	_socket->send_to(boost::asio::buffer(data), _endpoint);
}

void SGame::destroyEntity(const boost::property_tree::ptree &mRoot)
{
	for (auto &e :_manager.getEntities()) {
		if (e->getId() == mRoot.get<int>("ID")) {
			e->destroy();
			_manager.refresh();
			break;
		}
	}
}

void SGame::moveEntity(const boost::property_tree::ptree &mRoot)
{
	sf::Vector2f newpos(mRoot.get<int>("X"), mRoot.get<int>("Y"));

	for (auto &e : _manager.getEntities()) {
		if (e->getId() == mRoot.get<int>("ID")) {
			e->getComponent<PositionComponent>().setPosition(newpos);
			e->getComponent<GraphicsComponent>().setPosition(newpos);
		}
	}
}