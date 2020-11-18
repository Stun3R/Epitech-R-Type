/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "SJoin.hpp"
#include "../../Client.hpp"

SJoin::SJoin(Client *mContext) : _context(mContext), _window(&mContext->getWindow())
{
	_socket = _context->getSocket();
	_endpoint = _context->getEndpoint();
	_texture.loadFromFile("assets/UI/Background/Join_bg.png");
	_sprite.setTexture(_texture);
	_waitText = textFactory("Waiting ...", 0);

	_command["LIST"] = std::bind(&SJoin::feedList, this, std::placeholders::_1);
	_command["NEWPLAYER"] = std::bind(&SJoin::createPlayer, this, std::placeholders::_1);
	_command["NEWCOOP"] = std::bind(&SJoin::createCoop, this, std::placeholders::_1);
	_command["DESTROY"] = std::bind(&SJoin::destroyEntity, this, std::placeholders::_1);
	_command["LEAVE"] = std::bind(&SJoin::leaveRoom, this, std::placeholders::_1);
	_command["LAUNCH"] = std::bind(&SJoin::launch, this, std::placeholders::_1);

	boost::property_tree::ptree root;
	root.put("TYPE", "LIST");
	sendServer(root);
}

bool checkMouseClick(sf::Text &mText, sf::Vector2f mousePosition)
{
	return mText.getGlobalBounds().contains(mousePosition);
}

void SJoin::input()
{
	boost::property_tree::ptree root;

	sf::Vector2i mouse;
	if (!_click && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		mouse = sf::Mouse::getPosition(_window->getWindow());
		for (auto &l : _viewList)
			if (checkMouseClick(l, sf::Vector2f(mouse))) {
				_roomName = static_cast<std::string>(l.getString()).erase(l.getString().getSize() - 6);
				root.put("TYPE", "JOIN");
				root.put("ROOM", _roomName);
				sendServer(root);
				_click = true;
				_wait = true;
			}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		boost::property_tree::ptree newroot;
		newroot.put("TYPE", "ROOM");
		newroot.put("ACTION", "QUIT");
		newroot.put("ROOM", _roomName);
		newroot.put("ID", _id);
		sendServer(newroot);
		_context->setState(new SHome(_context));
	}
}

void SJoin::draw()
{
	_window->getWindow().draw(_sprite);
	if (!_wait) {
		for (auto &l : _viewList)
			_window->getWindow().draw(l);
	} else
		_window->getWindow().draw(_waitText);
}

void SJoin::handleReceive(const boost::property_tree::ptree &mRoot)
{
	std::string type = mRoot.get<std::string>("TYPE");
	std::map<std::string, std::function<void(const boost::property_tree::ptree &)>>::iterator it;
	for (it = _command.begin(); it != _command.end(); it++)
		if (it->first == type)
			it->second(mRoot);
}

void SJoin::feedList(const boost::property_tree::ptree &root)
{
	int mPadding = 100;
	for (auto &room : root.get_child("ROOMS")) {
		std::string item = room.first + " - " + room.second.data() + "/4";
		_viewList.push_back(textFactory(item, mPadding));
		mPadding -= 50;
	}
}

sf::Text SJoin::textFactory(const std::string &text, int mPadding)
{
	sf::Vector2u mWindowSize = _context->getWindow().getWindow().getSize();
	sf::Text mText;

	mText.setFont(_window->getFont());
	mText.setString(text);
	mText.setCharacterSize(64);
	mText.setPosition((mWindowSize.x / 2) - (mText.getGlobalBounds().width / 2),
		(mWindowSize.y / 2) - (mText.getGlobalBounds().height / 2) - mPadding);
	mText.setFillColor(sf::Color::White);
	return mText;
}

void SJoin::sendServer(const boost::property_tree::ptree &mRoot)
{
	std::ostringstream buf;
	write_json(buf, mRoot, false);
	std::string data = buf.str();
	_socket->send_to(boost::asio::buffer(data), _endpoint);
}

void SJoin::createPlayer(const boost::property_tree::ptree &mRoot)
{
	sf::Vector2f mPos(mRoot.get<int>("X"), mRoot.get<int>("Y"));

	auto &e = _manager.addEntity(std::stoi(mRoot.get<std::string>("ID")));
	e.addComponent<PositionComponent>(mPos);
	e.addComponent<HealthComponent>();
	e.addComponent<PowerComponent>();
	e.addComponent<SpeedComponent>(Speed::Medium);
	e.addComponent<NicknameComponent>(mRoot.get<std::string>("NAME"));
	e.addComponent<GraphicsComponent>("assets/Players/" + mRoot.get<std::string>("NAME") + "/1.png");
	e.addComponent<ScoreComponent>();
	e.addGroup(GameGroup::Player);

	_id = mRoot.get<int>("ID");
}

void SJoin::createCoop(const boost::property_tree::ptree &mRoot)
{
	sf::Vector2f mPos(mRoot.get<int>("X"), mRoot.get<int>("Y"));

	auto &e = _manager.addEntity(std::stoi(mRoot.get<std::string>("ID")));
	e.addComponent<PositionComponent>(mPos);
	e.addComponent<HealthComponent>();
	e.addComponent<PowerComponent>();
	e.addComponent<SpeedComponent>(Speed::Medium);
	e.addComponent<NicknameComponent>(mRoot.get<std::string>("NAME"));
	e.addComponent<GraphicsComponent>("assets/Players/" + mRoot.get<std::string>("NAME") + "/1.png");
	e.addComponent<ScoreComponent>();
	e.addGroup(GameGroup::Player);
}

void SJoin::destroyEntity(const boost::property_tree::ptree &mRoot)
{
	for (auto &e :_manager.getEntities()) {
		if (e->getId() == mRoot.get<int>("ID")) {
			e->destroy();
			_manager.refresh();
		}
	}
}

void SJoin::leaveRoom(const boost::property_tree::ptree &mRoot)
{
	_context->setState(new SHome(_context));
}

void SJoin::launch(const boost::property_tree::ptree &mRoot)
{
	_context->setState(new SGame(_context, _manager, _id, _roomName));
}
