/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "SpeedComponent.hpp"

SpeedComponent::SpeedComponent(Speed mSpeed) : _speed(mSpeed)
{
}

Speed SpeedComponent::getSpeed() const
{
	return _speed;
}

void SpeedComponent::setSpeed(Speed mSpeed)
{
	_speed = mSpeed;
}
