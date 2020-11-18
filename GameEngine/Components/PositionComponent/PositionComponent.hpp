/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef POSITIONCOMPONENT_HPP
#define POSITIONCOMPONENT_HPP

#include "../Component.hpp"

class PositionComponent : public Component {
	public:
	PositionComponent(const sf::Vector2f &);

	float x() const noexcept;

	float y() const noexcept;

	void setPosition(const sf::Vector2f &);

	void move(float x, float y);

	sf::Vector2f getPosition() const;

	private:
	sf::Vector2f _position;
};

#endif //POSITIONCOMPONENT_HPP
