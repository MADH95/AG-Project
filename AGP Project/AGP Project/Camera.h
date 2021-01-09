#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Spoonity {

	//Default values for major variables
	constexpr float YAW = -90.0f;
	constexpr float PITCH = 0.0f;
	constexpr float FOV = 45.0f;

	class Camera
	{

	//Member variables
	public:
		constexpr static glm::vec3 _WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 _Position;
		glm::vec3 _Front;
		glm::vec3 _Up;
		glm::vec3 _Right;

		float _Yaw;
		float _Pitch;

		float _FOV;

	//Functions
	public:

		//Constructor
		Camera(glm::vec3 position, glm::vec3 front, float yaw = YAW, float pitch = PITCH, float fov = FOV);

		//Returns the direction the player is looking to translate objects into view space
		glm::mat4 GetViewMatrix() const;

		//Reacalculates the cameras direction vectors
		void updateCameraVectors();
	};
}