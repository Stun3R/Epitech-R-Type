/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../System.hpp"

class Manager;

class MovementSystem : public System {
	public:
	MovementSystem(Manager &mManager);
	void updateEntities(float delta) override;
};

#endif //MOVEMENTSYSTEM_HPP
