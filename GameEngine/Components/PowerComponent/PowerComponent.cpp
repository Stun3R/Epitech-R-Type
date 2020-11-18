/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "PowerComponent.hpp"

PowerComponent::PowerComponent() : _power(0)
{
}

int PowerComponent::getPower() const
{
	return _power;
}

void PowerComponent::setPower(int mPower)
{
	PowerComponent::_power = mPower;
}
