/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef SPEEDCOMPONENT_HPP
#define SPEEDCOMPONENT_HPP

#include "../Component.hpp"
#include "../../Enum.hpp"

class SpeedComponent : public Component{
	public:
	SpeedComponent(Speed);

	Speed getSpeed() const;

	void setSpeed(Speed);

	private:
	Speed _speed;
};

#endif //SPEEDCOMPONENT_HPP
