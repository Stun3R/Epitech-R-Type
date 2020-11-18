/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "ScoreComponent.hpp"

ScoreComponent::ScoreComponent() : _score(0)
{
}

int ScoreComponent::getScore() const
{
	return _score;
}

void ScoreComponent::setScore(int mScore)
{
	_score = mScore;
}

void ScoreComponent::addScore(int mScore)
{
	_score = _score + mScore;
}