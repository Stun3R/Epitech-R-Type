/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../Library.hpp"
#include "../Manager/Manager.hpp"

class Component;

using ComponentID = std::size_t;


// SCreate NameSpace to hide the implementation details
namespace Internal {
	inline ComponentID getComponentID()
	{
		static ComponentID lastID = 0;
		return lastID++;
	}
}

template<typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
	static ComponentID typeID = Internal::getComponentID();
	return typeID;
}

// Number of Maximum Components
constexpr std::size_t maxComponents = 32;
// typedef for components to find them
using ComponentBitset = std::bitset<maxComponents>;
// typedef for components to stock them
using ComponentArray = std::array<Component *, maxComponents>;

class Entity {
	private:
	Manager &_manager;

	bool _alive = true;
	std::vector<std::unique_ptr<Component>> _components;
	ComponentArray _componentArray;
	ComponentBitset _componentBitSet;

	GroupBitset _groupBitSet;
	int _id;
	public:
	Entity(Manager &mManager, int);

	bool isAlive() const;

	void destroy();

	template<typename T>
	bool hasComponent() const
	{
		return _componentBitSet[getComponentTypeID<T>()];
	}

	bool hasGroup(Group mGroup) const noexcept;

	void addGroup(Group mGroup) noexcept;

	void delGroup(Group mGroup) noexcept;

	template<typename T, typename... TArgs>
	T &addComponent(TArgs... mArgs)
	{
		// check if Entity doesn't already has the Component
		assert(!hasComponent<T>());
		T *c(new T(std::forward<TArgs>(mArgs)...));
		c->_entity = this;
		std::unique_ptr<Component> uPtr(c);
		_components.emplace_back(std::move(uPtr));

		// Add component to the array and the BitSet
		_componentArray[getComponentTypeID<T>()] = c;
		_componentBitSet[getComponentTypeID<T>()] = true;

		return *c;
	}

	template<typename T>
	T &getComponent() const
	{
		// Check if entity hasComponent
		assert(hasComponent<T>());
		auto ptr(_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T *>(ptr);
	}

	int getId() const;
};

#endif //ENTITY_HPP
