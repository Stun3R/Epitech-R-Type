/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "../GameEngine.hpp"

void Manager::update(float delta)
{
	for (auto &s : _systems)
		s->updateEntities(delta);
}

void Manager::refresh()
{
	// browse all Groups to find dead Entity or Entity with incorrect Group
	for (std::size_t i = 0; i < maxGroups; i++) {
		auto &v = _groupedEntities[i];
		// Erase from the block the dead Entity and Entity with incorrect Group
		v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity *mEntity) {
			return !mEntity->isAlive() || !mEntity->hasGroup(i);
		}), std::end(v));
	}

	// erase all Entity that are dead
	_entities.erase(
		std::remove_if(std::begin(_entities), std::end(_entities), [](const std::shared_ptr<Entity> &mEntity) {
			return !mEntity->isAlive();
		}), std::end(_entities));
}

void Manager::addToGroup(Entity *mEntity, Group mGroup)
{
	_groupedEntities[mGroup].emplace_back(mEntity);
	// Check if group already has mEntity to optimize block
}

std::vector<Entity *> &Manager::getEntitiesByGroup(Group mGroup)
{
	return _groupedEntities[mGroup];
}

Entity &Manager::addEntity(int mID)
{
	auto *e = new Entity(*this, mID);
	std::shared_ptr<Entity> uPtr(e);
	_entities.emplace_back(std::move(uPtr));
	return *e;
}

std::vector<std::shared_ptr<Entity>> &Manager::getEntities()
{
	return _entities;
}

Entity *Manager::getPlayerById(int mId)
{
	for (auto &entity : getEntitiesByGroup(GameGroup::Player)) {
		if (entity->getId() == mId)
			return entity;
	}
	return nullptr;
}
