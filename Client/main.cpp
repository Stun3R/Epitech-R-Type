/*
** EPITECH PROJECT, 2021
** simple_example
** File description:
** Created by stun3r,
*/

#include "Client.hpp"

int main(int ac, char **av)
{
	Client	client;

	if (ac != 3) {
		std::cerr << "Usage: " << av[0] << "\thost port" << std::endl;
		return EXIT_FAILURE;
	}
	client.init(av[1], av[2]);
	client.run();
	return EXIT_SUCCESS;
}