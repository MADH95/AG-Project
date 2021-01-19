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
		Skybox* _Skybox;

	private:
		const Window* _Window;
		const Camera* _Camera;

		Shader _DepthShader, _GeometryShader, _LightingShader, debugDepthShader;

		const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

		unsigned int _DepthMapFBO, _DepthMap;

		unsigned int _gBuffer, _gPosition, _gNormal, _gAlbedoSpec;

		unsigned int quadVAO, quadVBO;

		//TODO: lighting class/rename
		glm::vec3 _LightPosition, _LightDirection, _LightColor; // Note light position isn't used for directional lights and light direction isn't used for point lights

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