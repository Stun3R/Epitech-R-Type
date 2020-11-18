/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

#include "../../Enum.hpp"
#include "../Component.hpp"

class GraphicsComponent : public Component {
	public:
	GraphicsComponent(const std::string &);

	const sf::Sprite &getSprite() const;

	void setSprite(const sf::Sprite &);

	void setTexture(const std::string &);

	const sf::Texture &getTexture() const;

	void setPosition(const sf::Vector2f &);

	private:
	sf::Sprite _sprite;
	sf::Texture _texture;
};

#endif //GRAPHICSCOMPONENT_HPP
