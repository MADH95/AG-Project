/*
Conventions:

----Variables----
constants = CAPITALISED_VARIABLE
Class Member variables    = _CamelCase
Struct Member variables = camelCase
Function parameters = camelCase
Temporary variables = camelCase

Related variables should be grouped
Unrelated variables should be separated by a new line
Variable assignement in groups should be lined up vertically

----Functions----
Function names = camelCase

----Classes----
Member variables and Functions have separate access modifier headings
Functions called by other functions should be declared higher up
Similar functions should be grouped together
Functions that don't modify member variables should be declared as const where possible

----Structs----
Struct declarations = StructName

----Comments----
Access modifier headings should have comments if they are the start of variable declaration or functions declaration
Functions should have comments above them with a brief description

----Shaders----
Shader names = shader_name.vs/fs/gs
*/

#include <iostream>

#include "Engine.h"
#include "Game.h"

using namespace Spoonity;

int main()
{
	Engine* engine = new Game();

	try {

		while (engine->isRunning())
		{
			engine->runtimeLoop();
		}

		delete engine;
		return 0;
	}
	//Catch and display thrown exceptions in console
	catch (const char* exceptionMessage)
	{
		delete engine;

		std::cout << exceptionMessage << std::endl;

		std::cin.get();
		return -1;
	}
}