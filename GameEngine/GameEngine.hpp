/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef ECS_HPP
#define ECS_HPP

#include "Library.hpp"

#include "Enum.hpp"

#include "Manager/Manager.hpp"
#include "Entity/Entity.hpp"
#include "Components/Component.hpp"
#include "Components/DamageComponent/DamageComponent.hpp"
#include "Components/DeliverComponent/DeliverComponent.hpp"
#include "Components/GraphicsComponent/GraphicsComponent.hpp"
#include "Components/HealthComponent/HealthComponent.hpp"
#include "Components/NicknameComponent/NicknameComponent.hpp"
#include "Components/PositionComponent/PositionComponent.hpp"
#include "Components/PowerComponent/PowerComponent.hpp"
#include "Components/PowerupComponent/PowerupComponent.hpp"
#include "Components/SpeedComponent/SpeedComponent.hpp"
#include "Components/ScoreComponent/ScoreComponent.hpp"
#include "System/System.hpp"
#include "System/MovementSystem/MovementSystem.hpp"

class GameEngine {
	public:
	GameEngine();

	Entity &createPlayer(const sf::Vector2f &, const std::string &, GameGroup);

	Entity &createMonster(const sf::Vector2f &, int, int);

	Entity &createObstacle(const sf::Vector2f &, int, Speed);

	Entity &createPowerUp(const sf::Vector2f &);

	void runExample();

	private:
	Manager _manager;
};

#endif //ECS_HPP
