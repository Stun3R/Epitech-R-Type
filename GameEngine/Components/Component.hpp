/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../Library.hpp"

class Entity;

class Component {
	public:
	Entity *_entity;

	virtual ~Component() {};
};

#endif //COMPONENT_H
