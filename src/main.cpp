/*
** EPITECH PROJECT, 2018
** bootstrap-arcade
** File description:
** main.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "Arcade.hpp"
#include "Error.hpp"


int main(int argc, char **argv)
{
	try {
		if (argc == 2) {
			ICoreProgram *arcade = new MyArcade(argv[1]);
			arcade->run();
		}
		else {
			throw Handler("main", "bad arguments");
		}
	}
	catch (Handler &e) {
		std::cerr << e.what();
		return (84);
	}
	return (0);
}
