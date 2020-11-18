//
// Created by stun3r on 26/11/18.
//

#include "HealthComponent.hpp"
#include "../../GameEngine.hpp"

HealthComponent::HealthComponent() : _health(1), _shield(0)
{
}

HealthComponent::HealthComponent(int mHealth, int mShield) : _health(mHealth), _shield(mShield)
{

}

int HealthComponent::getHealth() const
{
	return _health;
}

void HealthComponent::setHealth(int mHealth)
{
	_health = mHealth;
}

int HealthComponent::getShield() const
{
	return _shield;
}

void HealthComponent::setShield(int mShield)
{
	_shield = mShield;
}
