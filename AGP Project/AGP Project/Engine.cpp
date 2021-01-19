#include "Engine.h"

namespace Spoonity {

	Engine::Engine(Actor* player)
		: _LastFrame(0.0f), _DeltaTime(0.0f),
		_Player(player)
	{
		_Window = new Window(WindowProps("Advanced Graphics Project", 1920, 1080));

		_Renderer = new Renderer(_Window, _Player->_Camera);

		//Initialize input
		Input::setWindow(_Window);
	}

	Engine::~Engine()
	{
		Input::clearWindow();

		delete _Renderer;
		delete _Window;
		delete _Player;
	}

	//Function for controlling runtime loop
	void Engine::runtimeLoop()
	{
		//Per-frame time logic
		float currentFrame = (float)glfwGetTime();
		_DeltaTime = currentFrame - _LastFrame;
		_LastFrame = currentFrame;

		//Input
		glfwPollEvents();

		//Run gameloop
		gameLoop(_DeltaTime);

		//Render
		_Renderer->renderScene();
	}

	//Function to check if the engine is running
	bool Engine::isRunning() const
	{
		return !glfwWindowShouldClose(_Window->getInstance());
	}
}