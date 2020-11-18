//
// Created by stun3r on 26/11/18.
//

#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent(const std::string &mPath)
{
	setTexture(mPath);
	_sprite.setTexture(_texture);
}

const sf::Sprite &GraphicsComponent::getSprite() const
{
	return _sprite;
}

void GraphicsComponent::setSprite(const sf::Sprite &mSprite)
{
	_sprite = mSprite;
}

void GraphicsComponent::setTexture(const std::string &mPath)
{
	if (!_texture.loadFromFile(mPath))
		exit(EXIT_FAILURE);
}

const sf::Texture &GraphicsComponent::getTexture() const
{
	return _texture;
}

void GraphicsComponent::setPosition(const sf::Vector2f &mNewPos)
{
	_sprite.setPosition(mNewPos);
}
