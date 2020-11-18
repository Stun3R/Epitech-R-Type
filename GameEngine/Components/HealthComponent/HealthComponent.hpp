/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include "../Component.hpp"

class HealthComponent : public Component {
	public:
	HealthComponent();
	HealthComponent(int, int);

	int getHealth() const;

	void setHealth(int);

	int getShield() const;

	void setShield(int _shield);

	private:
	int _health;
	int _shield;
};

#endif //HEALTHCOMPONENT_HPP
