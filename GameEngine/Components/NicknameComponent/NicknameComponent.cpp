/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#include "NicknameComponent.hpp"

NicknameComponent::NicknameComponent(const std::string &mNickname) : _nickname(mNickname)
{
}

const std::string &NicknameComponent::getNickname() const
{
	return _nickname;
}

void NicknameComponent::setNickname(const std::string &mNickname)
{
	_nickname = mNickname;
}
