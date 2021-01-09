#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"

class Game : public Spoonity::Engine
{
//Variables
public:
	std::vector<Spoonity::Scene*> _Scenes;

//Functions
public:

	//Constructor
	Game();

	//Destructor
	~Game();

	//Overriding gameloop
	void gameLoop(float& deltaTime) override;

	//Load default scene
	Spoonity::Scene* loadOverworld();
};