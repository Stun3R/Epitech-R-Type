/*
** EPITECH PROJECT, 2021
** R-TYPE
** File description:
** Created by stun3r,
*/

#ifndef NICKNAMECOMPONENT_HPP
#define NICKNAMECOMPONENT_HPP

#include "../Component.hpp"

class NicknameComponent : public Component {
	public:
	NicknameComponent(const std::string &);

	const std::string &getNickname() const;

	void setNickname(const std::string &);

	private:
	std::string _nickname;
};

#endif //NICKNAMECOMPONENT_HPP
