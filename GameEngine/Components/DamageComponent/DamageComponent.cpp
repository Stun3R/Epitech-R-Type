/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "DamageComponent.hpp"

DamageComponent::DamageComponent(std::size_t mDamage) : _damage(mDamage)
{
}

size_t DamageComponent::getDamage() const
{
	return _damage;
}

void DamageComponent::setDamage(std::size_t mDamage)
{
	_damage = mDamage;
}
