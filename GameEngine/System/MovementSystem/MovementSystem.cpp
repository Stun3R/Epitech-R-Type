//
// Created by stun3r on 25/11/18.
//

#include "../../GameEngine.hpp"

MovementSystem::MovementSystem(Manager &mManager) : System(mManager)
{
}

void MovementSystem::updateEntities(float delta)
{
	auto &entity = _manager.getEntitiesByGroup(GameGroup::Blue);
	for (auto &e : entity) {
		sf::Vector2f position = e->getComponent<PositionComponent>().getPosition();
		position.x++;
		position.y++;
		e->getComponent<PositionComponent>().setPosition(position);
	}
}
