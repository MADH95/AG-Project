#pragma once
#include "Shader.h"
#include "Camera.h"

namespace Spoonity {

	struct ObjectData {
		float speed;
		glm::vec2 angle;
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 scale;

		ObjectData(const glm::vec3& position = glm::vec3(0.0f),
				   const glm::vec2& angle = glm::vec2(0.0f),
				   const glm::vec3& front = glm::vec3(1.0f, 0.0f, 0.0f),
				   const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
				   const glm::vec3& scale = glm::vec3(1.0f),
				   const float speed = 0.0f)
			: position(position), angle(angle), front(front), up(up), right(glm::cross(front, up)), scale(scale), speed(speed) 
		{
		}

		void updateVectors()
		{
			right = glm::cross(front, up);
			up = glm::cross(right, front);
		}
	};

	class GameObject
	{
	//Variables
	public:
		ObjectData _Data;

	protected:
		bool _IsEnabled;

	//Functions
	public:

		//Constructors
		GameObject() :_Data(ObjectData()) {}

		GameObject(const ObjectData &data,
				   const bool &enabled = false)
			: _Data(data), _IsEnabled(enabled)
		{
		}

		//Destructor
		virtual ~GameObject() {}

		//Render the object
		virtual void draw(const Shader &shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model) = 0;

		//Update the object
		virtual void update(float &deltaTime) = 0;

		//Enable object to be rendered and process physics
		void enable()
		{
			_IsEnabled = true;
		}

		//Disable object from being rendered and processing physics
		void disable()
		{
			_IsEnabled = false;
		}
	};
}