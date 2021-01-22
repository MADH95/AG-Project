#include "Game.h"

#include "GameObject.h"
#include "Skybox.h"
#include "Entity.h"
#include "Glasses.h"

//Constructor
Game::Game() : Engine( new Player(Spoonity::ObjectData()))
{
	_DefaultShader = Spoonity::Shader("Data/Shaders/PostProcessing/Default/default_shader.vs", "Data/Shaders/PostProcessing/Default/default_shader.fs");

	_Player->_IsSpeccyBastard = false;

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
	//Update the player
	_Player->update(deltaTime);

	for (auto it = _Scenes.begin(); it != _Scenes.end(); it++)
	{
		if ((*it)->_ID == Level::Overworld)
		{
			(*it)->update(deltaTime);
		}
	}

	//Ghetto Collision detection
	for (auto scene = _Scenes.begin(); scene < _Scenes.end(); scene++)
	{
		//Check the correct scene
		if ((*scene)->_ID == Level::Overworld)
		{
			//Loop through the objects in the scene
			for (auto obj = (*scene)->_SceneObjects->begin(); obj < (*scene)->_SceneObjects->end(); obj++)
			{
				//Try to cast the object to a Glasses
				Glasses* specs = dynamic_cast<Glasses*>(*obj);

				//Only do collision detection if it is a Glasses object
				if (specs)
				{
					//Get the distance between the object and the player
					float distance = glm::length(specs->_Data.position - _Player->_Data.position);

					//If the distance is within range, and the render shader is not the same as the collided specs
					if (distance <= 0.2f && _Renderer->_PostProcessShader._ID != specs->_PostProcessShader._ID)
					{
						//std::cout << "Collided!" << std::endl;
						//Set the rederer post processing shader to the specific one for those specs
						_Renderer->_PostProcessShader = specs->_PostProcessShader;

						_Player->_IsSpeccyBastard = true;
						_Specs->enable();
					}
				}

				//Null out specs
				specs = nullptr;
			}
		}
	}

	if (_Player->_IsSpeccyBastard)
	{
		glm::vec3 offset = glm::vec3(0.0f, 0.1991f, 0.0f) + (_Player->_Data.front * 0.008f);
		_Specs->_Data.position = _Player->_Data.position + offset;

		_Specs->_Data.angle.x = _Player->_Data.angle.x + 90.0f;
		_Specs->_Data.angle.y = _Player->_Data.angle.y;
	}
	else
	{
		_Specs->disable();
		_Renderer->_PostProcessShader = _DefaultShader;
	}
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
		Spoonity::Shader("Data/Shaders/Skybox/skybox_shader.vs", "Data/Shaders/Skybox/skybox_shader.fs")
	);

	_Renderer->_Skybox = sky;

	//Add the objects to the scene
	objs->emplace_back(sky);

	Spoonity::Entity* demo = new Spoonity::Entity(
		Spoonity::ObjectData(
			glm::vec3(0.0f),
			glm::vec2(0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.005f)
		),
		"Data/Models/SyntyStudios/PolygonWestern/western.fbx"
	);

	demo->enable(); //enable the object to be drawn

	objs->emplace_back(demo);

	//TODO: add other objects as required.
	
	std::vector<glm::vec3> positions {
		glm::vec3(6.19f, 0.5f, -9.09f),
		glm::vec3(-6.52f, 0.5f, -25.25f),
		glm::vec3(6.28f, 0.5f, -19.57f),
		glm::vec3(-8.32f, 0.5f, 59.79f),
		glm::vec3(52.80f, 0.5f, -1.80)
	};
	
	std::vector<Spoonity::Shader> shaders{
		Spoonity::Shader("Data/Shaders/PostProcessing/Greyscale/greyscale_shader.vs", "Data/Shaders/PostProcessing/Greyscale/greyscale_shader.fs"), // Greyscale shader
		Spoonity::Shader("Data/Shaders/PostProcessing/X-Ray/x-ray_shader.vs", "Data/Shaders/PostProcessing/X-Ray/x-ray_shader.fs"), // X-Ray shader
		Spoonity::Shader("Data/Shaders/PostProcessing/EdgeDetection/edgedetection_shader.vs", "Data/Shaders/PostProcessing/EdgeDetection/edgedetection_shader.fs"), // Edge Detection shader
		Spoonity::Shader("Data/Shaders/PostProcessing/DeepFry/deepfry_shader.vs", "Data/Shaders/PostProcessing/DeepFry/deepfry_shader.fs"), // Deep Fry Shader
		Spoonity::Shader("Data/Shaders/PostProcessing/Sepia/sepia_shader.vs", "Data/Shaders/PostProcessing/Sepia/sepia_shader.fs") // Sepia Shader
	};
	
	Glasses* specs;

	for (int i = 0; i < positions.size(); i++)
	{
		specs = new Glasses(
			Spoonity::ObjectData(
				positions[i],
				glm::vec2(0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(0.1f)
			),
			"Data/Models/Glasses/oculos.obj",
			shaders[i]
		);

		specs->enable();
		objs->emplace_back(specs);
	}

	Spoonity::Entity* wearableGlasses = new Spoonity::Entity(
		Spoonity::ObjectData(
			glm::vec3(0.0f, -10.0f, 0.0f),
			glm::vec2(0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0401f, 0.0452f, -0.01f)
		),
		"Data/Models/Glasses/oculos.obj"
	);

	wearableGlasses->enable();

	objs->emplace_back(wearableGlasses);

	_Specs = wearableGlasses;

	//Return a scene with the added objects
	return new Spoonity::Scene(Level::Overworld, objs);
}