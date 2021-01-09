#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Player.h"

namespace Spoonity {

	class Engine
	{

	//Memeber variables
	protected:
		Window* _Window;

		Renderer* _Renderer;

		Actor* _Player;
		
		float _LastFrame;

	public:
		float _DeltaTime;

	//Functions
	public:

		//Constructor
		Engine(Actor* player);

		//Destructor
		virtual ~Engine();

		//Function to check if the engine is running
		bool isRunning() const;

		//Function for controlling runtime loop
		void runtimeLoop();

	private:
		virtual void gameLoop(float& deltaTime) = 0;
	};
}