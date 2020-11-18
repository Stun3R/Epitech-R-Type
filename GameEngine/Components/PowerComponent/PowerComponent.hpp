/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef POWERCOMPONENT_HPP
#define POWERCOMPONENT_HPP

#include "../Component.hpp"

class PowerComponent : public Component {
	public:
	PowerComponent();

	int getPower() const;

	void setPower(int);

	private:
	int _power;
};

#endif //POWERCOMPONENT_HPP
