/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "PositionComponent.hpp"

PositionComponent::PositionComponent(const sf::Vector2f &mPosition) : _position(mPosition)
{
}

float PositionComponent::x() const noexcept
{
	return _position.x;
}

float PositionComponent::y() const noexcept
{
	return _position.y;
}

void PositionComponent::setPosition(const sf::Vector2f &mPosition)
{
	_position = mPosition;
}

sf::Vector2f PositionComponent::getPosition() const
{
	return _position;
}

void PositionComponent::move(float x, float y)
{
	_position.x += x;
	_position.y += y;
}

