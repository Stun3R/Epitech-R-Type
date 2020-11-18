/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef ENUM_HPP
#define ENUM_HPP

#include "Library.hpp"

enum GameGroup : std::size_t {
	Player,
	Blue,
	Red,
	Yellow,
	Green,
	Monster,
	Obstacle,
	PowerUp
};

enum Speed {
	None = 0,
	Slow = 1,
	Medium = 2,
	Fast = 3
};

#endif //ENUM_HPP
