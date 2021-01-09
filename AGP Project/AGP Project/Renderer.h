#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "stb_image.h"

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Scene.h"

#include "GameObject.h"
#include "Skybox.h"

namespace Spoonity {

	class Renderer
	{

	//Variables
	public:
		Shader _PostProcessShader;

		Scene* _CurrentScene;

	private:
		const Window* _Window;
		const Camera* _Camera;

		Shader _LightingShader, _LightsShader;

		unsigned int _gBuffer, _gPosition, _gNormal, _gAlbedoSpec;

		unsigned int quadVAO, quadVBO;

		//TODO: lighting class/rename
		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;

	//Functions
	public:

		//Constructors
		Renderer();

		Renderer(const Window* window, const Camera* camera);

		//Destructor
		~Renderer();

		//Function for configuring buffers
		void genBuffers();

		//Render the scene
		void renderScene();
	};
}