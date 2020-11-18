/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef POWERUPCOMPONENT_HPP
#define POWERUPCOMPONENT_HPP

#include "../Component.hpp"

enum Type {
	Health,
	Shield,
	Power
};

class PowerupComponent : public Component {
	public:
	PowerupComponent(Type, int);

	Type getType() const;

	void setType(Type);

	int getValue() const;

	void setValue(int);

	private:
	Type _type;
	int _value;
};

#endif //POWERUPCOMPONENT_HPP
