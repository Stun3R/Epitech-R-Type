/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "../Library.hpp"

using Group = std::size_t;

class Entity;

class System;

// Number of Maximum Groups
constexpr std::size_t maxGroups = 32;
// typedef for entities to find them
using GroupBitset = std::bitset<maxGroups>;
// typedef for groups to store Entities
using GroupedEntities = std::array<std::vector<Entity *>, maxGroups>;

class Manager {
	private:
	std::vector<std::shared_ptr<System>> _systems;
	std::vector<std::shared_ptr<Entity>> _entities;
	// Store entity in Group to better manage them
	GroupedEntities _groupedEntities;
	public:
	void update(float delta);

	void refresh();

	Entity &addEntity(int mID);

	// To add an Entity to a Group we emplace_back the Entity in the corresponding block
	void addToGroup(Entity *mEntity, Group mGroup);

	std::vector<Entity *> &getEntitiesByGroup(Group mGroup);

	std::vector<std::shared_ptr<Entity>> &getEntities();

	Entity *getPlayerById(int mId);

	template<typename T, typename... TArgs>
	T &addSystem(TArgs... mArgs)
	{
		T *s(new T(*this, std::forward<TArgs>(mArgs)...));
		std::shared_ptr<System> uPtr(s);
		_systems.emplace_back(std::move(uPtr));

		return *s;
	}
};

#endif //MANAGER_HPP
