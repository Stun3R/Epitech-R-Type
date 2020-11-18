/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef SCORECOMPONENT_HPP
#define SCORECOMPONENT_HPP

#include "../Component.hpp"

class ScoreComponent : public Component {
	public:
	ScoreComponent();

	int getScore() const;

	void setScore(int);

	void addScore(int);

	private:
	int _score;
};

#endif //SCORECOMPONENT_HPP
