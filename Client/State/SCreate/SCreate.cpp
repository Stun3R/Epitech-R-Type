/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "SCreate.hpp"
#include "../../Client.hpp"

SCreate::SCreate(Client *mContext) : _context(mContext), _window(&mContext->getWindow())
{
	_socket = _context->getSocket();
	_endpoint = _context->getEndpoint();
	_bgTexture.loadFromFile("assets/UI/Background/Create_bg.png");
	_bgSprite.setTexture(_bgTexture);

	sf::Vector2u mWindowSize = _context->getWindow().getWindow().getSize();

	_stTexture.loadFromFile("assets/UI/Button/Ready.png");
	_stSprite.setTexture(_stTexture);
	_stSprite.setPosition((mWindowSize.x / 2) - (_stSprite.getGlobalBounds().width / 2), (mWindowSize.y / 2) + 100);

	_name.setFont(_window->getFont());
	_name.setString("");
	_name.setCharacterSize(72);
	_name.setPosition((mWindowSize.x / 2) - 180, (mWindowSize.y / 2) - 50);
	_name.setFillColor(sf::Color::White);

	_command["FAILED"] = std::bind(&SCreate::failed, this, std::placeholders::_1);
	_command["NEWPLAYER"] = std::bind(&SCreate::createPlayer, this, std::placeholders::_1);
	_command["NEWCOOP"] = std::bind(&SCreate::createCoop, this, std::placeholders::_1);
	_command["DESTROY"] = std::bind(&SCreate::destroyEntity, this, std::placeholders::_1);
	_command["LAUNCH"] = std::bind(&SCreate::launch, this, std::placeholders::_1);
}

void SCreate::input()
{
	sf::Event event;
	sf::Vector2i mouse;

	while (_context->getWindow().getWindow().pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			_context->getWindow().close();
			break;
		case sf::Event::LostFocus:
			_context->getWindow().setFocus(false);
			break;
		case sf::Event::GainedFocus:
			_context->getWindow().setFocus(true);
			break;
		case sf::Event::TextEntered:
			if ((event.text.unicode > 30 && (event.text.unicode < 128 || event.text.unicode > 159)) &&
				_roomName.size() < 10 && !_send) {
				_roomName += sf::String(event.text.unicode);
				_name.setString(_roomName);
			}
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::BackSpace:
				if (!_roomName.empty() && !_send) {
					_roomName.pop_back();
					_name.setString(_roomName);
				}
				break;
			case sf::Keyboard::Enter:
				if (!_roomName.empty() && !_send) {
					boost::property_tree::ptree root;
					root.put("TYPE", "CREATE");
					root.put("ROOM", _roomName);
					sendServer(root);
					_send = true;
				}
				break;
			case sf::Keyboard::Escape:
				if (!_roomName.empty()) {
					boost::property_tree::ptree root;
					root.put("TYPE", "DESTROY");
					root.put("ROOM", _roomName);
					root.put("ID", _id);
					sendServer(root);
				}
				_context->setState(new SHome(_context));
				break;
			}
		}
	}

	if (_send && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		mouse = sf::Mouse::getPosition(_window->getWindow());
		if (_stSprite.getGlobalBounds().contains(sf::Vector2f(mouse))) {
			boost::property_tree::ptree root;
			root.put("TYPE", "ROOM");
			root.put("ACTION", "READY");
			root.put("ROOM", _roomName);
			sendServer(root);
		}
	}
}

void SCreate::draw()
{
	_window->getWindow().draw(_bgSprite);
	_window->getWindow().draw(_name);
	if (_send)
		_window->getWindow().draw(_stSprite);
}

void SCreate::handleReceive(const boost::property_tree::ptree &mRoot)
{
	std::string type = mRoot.get<std::string>("TYPE");
	std::map<std::string, std::function<void(const boost::property_tree::ptree &)>>::iterator it;
	for (it = _command.begin(); it != _command.end(); it++)
		if (it->first == type)
			it->second(mRoot);
}

void SCreate::sendServer(const boost::property_tree::ptree &mRoot)
{
	std::ostringstream buf;
	write_json(buf, mRoot, false);
	std::string data = buf.str();
	_socket->send_to(boost::asio::buffer(data), _endpoint);
}

void SCreate::failed(const boost::property_tree::ptree &mRoot)
{
	_send = false;
}

void SCreate::createPlayer(const boost::property_tree::ptree &mRoot)
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

void SCreate::createCoop(const boost::property_tree::ptree &mRoot)
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

void SCreate::destroyEntity(const boost::property_tree::ptree &mRoot)
{
	for (auto &e :_manager.getEntities()) {
		if (e->getId() == mRoot.get<int>("ID")) {
			e->destroy();
			_manager.refresh();
		}
	}
}

void SCreate::launch(const boost::property_tree::ptree &mRoot)
{
	_context->setState(new SGame(_context, _manager, _id, _roomName));
}

