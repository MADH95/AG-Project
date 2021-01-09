#include "Game.h"

#include "GameObject.h"
#include "Skybox.h"
#include "Entity.h"
#include "Glasses.h"

//Constructor
Game::Game() : Engine( new Player(Spoonity::ObjectData()))
{

	//initEngine();

	_Scenes.emplace_back(loadOverworld());

	//Determine default scene, and pass it to the renderer.
	for (auto it = _Scenes.begin(); it != _Scenes.end(); it++)
	{
		if ((*it)->_ID == Level::Overworld)
		{
			_Renderer->_CurrentScene = *it;
		}
	}
}

//Destructor
Game::~Game()
{
	for (auto it = _Scenes.begin(); it != _Scenes.end(); ++it)
	{
		delete *it;
	}

	_Scenes.clear();
}

//Overriding gameloop
void Game::gameLoop(float& deltaTime)
{
	//TODO: Game logic
	_Player->update(deltaTime);
}

//Load default scene
Spoonity::Scene* Game::loadOverworld()
{
	//Create the objects vector to be passed to the scene
	std::vector<Spoonity::GameObject*> *objs = new std::vector<Spoonity::GameObject*>();

	Spoonity::Skybox* sky = new Spoonity::Skybox(
		Spoonity::ObjectData(),
		std::vector<std::string>(
			{
				"Data/Textures/skybox/right.jpg",
				"Data/Textures/skybox/left.jpg",
				"Data/Textures/skybox/top.jpg",
				"Data/Textures/skybox/bottom.jpg",
				"Data/Textures/skybox/front.jpg",
				"Data/Textures/skybox/back.jpg"
			}
		),
		Spoonity::Shader("Data/Shaders/skybox_shader.vs", "Data/Shaders/skybox_shader.fs")
	);

	//Add the objects to the scene
	objs->emplace_back(sky);

	Spoonity::Entity* demo = new Spoonity::Entity(
		Spoonity::ObjectData(
			glm::vec3(0.0f),
			/*Angle*/ 0.0f,
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.005f)
		),
		"Data/Models/SyntyStudios/PolygonWestern/western.fbx",
		Spoonity::Shader("Data/Shaders/geometry_shader.vs", "Data/Shaders/geometry_shader.fs")
	);

	demo->enable(); //enable the object to be drawn

	objs->emplace_back(demo);

	//TODO: add other objects as required.

	std::vector<glm::vec3> positions {
		glm::vec3(6.19f, 0.5f, -9.09f),
		glm::vec3(-6.52f, 0.5f, -25.25f),
		glm::vec3(6.28f, 0.5f, -19.57f),
		glm::vec3(-8.32f, 0.5f, 59.79f)
	};

	Glasses* specs;

	for (int i = 0; i < positions.size(); i++)
	{
		specs = new Glasses(
			Spoonity::ObjectData(
				positions[i],
				/*Angle*/ 0.0f,
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(0.1f)
			),
			"Data/Models/backpack/backpack.obj",
			Spoonity::Shader("Data/Shaders/geometry_shader.vs", "Data/Shaders/geometry_shader.fs"),
			Spoonity::Shader( /* TODO: Add post processing shader */)
		);

		specs->enable();
		objs->emplace_back(specs);
	}

	//Return a scene with the added objects
	return new Spoonity::Scene(Level::Overworld, objs);
}