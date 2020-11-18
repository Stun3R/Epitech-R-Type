/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "PowerupComponent.hpp"

PowerupComponent::PowerupComponent(Type mType, int mValue) : _type(mType), _value(mValue)
{
}

Type PowerupComponent::getType() const
{
	return _type;
}

void PowerupComponent::setType(Type mType)
{
	_type = mType;
}

int PowerupComponent::getValue() const
{
	return _value;
}

void PowerupComponent::setValue(int mValue)
{
	_value = mValue;
}
