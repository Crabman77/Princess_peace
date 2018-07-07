/*
 * main.cpp
 *
 *  Created on: 28 juin 2018
 *	  Author: Crabman
 */

#include <iostream>
#include "Engine.hpp"

int main(int argc, char *argv[])
{
	Engine engine;
	if (!engine.init())
	{
		return (EXIT_FAILURE);
	}
	engine.menu();
	engine.cleanup();
	return (EXIT_SUCCESS);
}
