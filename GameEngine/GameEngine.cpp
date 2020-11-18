/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "GameEngine.hpp"

GameEngine::GameEngine()
{
	_manager.addSystem<MovementSystem>();
	createPlayer(sf::Vector2f(20, 20), "PlayerExample" ,GameGroup::Blue);
}

Entity &GameEngine::createPlayer(const sf::Vector2f &mPosition,
	const std::string &mName, GameGroup mGroup)
{
	std::size_t id = 0;
	auto &entity = _manager.addEntity(id);
	entity.addComponent<PositionComponent>(mPosition);
	entity.addComponent<HealthComponent>();
	entity.addComponent<PowerComponent>();
	entity.addComponent<SpeedComponent>(Speed::Medium);
	entity.addComponent<NicknameComponent>(mName);
	entity.addComponent<ScoreComponent>();

	entity.addGroup(mGroup);
	return entity;
}

Entity &GameEngine::createMonster(const sf::Vector2f &mPosition, int mHealth, int mShield)
{
	std::size_t id = 0;
	auto &entity = _manager.addEntity(id);
	entity.addComponent<PositionComponent>(mPosition);
	entity.addComponent<HealthComponent>(mHealth, mShield);
	entity.addComponent<SpeedComponent>(Speed::Medium);

	entity.addGroup(GameGroup::Monster);
	return entity;
}

Entity &GameEngine::createObstacle(const sf::Vector2f &mPosition, int mHealth, Speed mSpeed)
{
	std::size_t id = 0;
	auto &entity = _manager.addEntity(id);
	entity.addComponent<PositionComponent>(mPosition);
	entity.addComponent<HealthComponent>(mHealth, 0);
	entity.addComponent<SpeedComponent>(mSpeed);

	entity.addGroup(GameGroup::Obstacle);
	return entity;
}

Entity &GameEngine::createPowerUp(const sf::Vector2f &mPosition)
{
	std::size_t id = 0;
	auto &entity = _manager.addEntity(id);
	entity.addComponent<PositionComponent>(mPosition);
	entity.addComponent<PowerupComponent>(Type::Health, 1);
	entity.addComponent<SpeedComponent>(Speed::None);

	entity.addGroup(GameGroup::PowerUp);
	return entity;
}

void GameEngine::runExample()
{
	auto &players = _manager.getEntities();
	bool running = true;

	while (running) {
		_manager.refresh();
		_manager.update(30);
		for (auto &player : players) {
			std::cout
				<< player->getComponent<NicknameComponent>().getNickname()
				<< " Pos X : "
				<< player->getComponent<PositionComponent>().x()
				<< " Pos Y : "
				<< player->getComponent<PositionComponent>().y()
				<< " HEALTH : "
				<< player->getComponent<HealthComponent>().getHealth()
				<< " SHIELD : "
				<< player->getComponent<HealthComponent>().getShield()
				<< " POWER : "
				<< player->getComponent<PowerComponent>().getPower()
				<< " SPEED : "
				<< player->getComponent<SpeedComponent>().getSpeed()
				<< std::endl;
		}
	}
}
