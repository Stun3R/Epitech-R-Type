/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef DAMAGECOMPONENT_HPP
#define DAMAGECOMPONENT_HPP

#include "../Component.hpp"

class DamageComponent : public Component {
	public:
	DamageComponent(std::size_t _damage);

	std::size_t getDamage() const;

	void setDamage(std::size_t _damage);

	private:
	std::size_t _damage;
};

#endif //DAMAGECOMPONENT_HPP
