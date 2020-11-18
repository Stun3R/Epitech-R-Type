/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "../GameEngine.hpp"

Entity::Entity(Manager &mManager, int mID) : _manager(mManager), _id(mID)
{
}

bool Entity::isAlive() const
{
	return _alive;
}

void Entity::destroy()
{
	_alive = false;
}

bool Entity::hasGroup(Group mGroup) const noexcept
{
	return _groupBitSet[mGroup];
}

void Entity::addGroup(Group mGroup) noexcept
{
	_groupBitSet[mGroup] = true;
	_manager.addToGroup(this, mGroup);
}

void Entity::delGroup(Group mGroup) noexcept
{
	// Manager will remove automatically entity that are not in group when he will update
	_groupBitSet[mGroup] = false;
}

int Entity::getId() const
{
	return _id;
}
