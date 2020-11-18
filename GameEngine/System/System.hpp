/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "../Library.hpp"

class Manager;

class System {
	public:
	Manager &_manager;

	explicit System(Manager &_manager) : _manager(_manager)	{
	}

	virtual void updateEntities(float delta) {};

	virtual ~System() {};

};

#endif //SYSTEM_HPP
