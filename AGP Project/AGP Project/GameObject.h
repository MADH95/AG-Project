#pragma once
#include "Shader.h"

namespace Spoonity {

	struct ObjectData {
		float speed, angle;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 scale;

		ObjectData(const glm::vec3& position = glm::vec3(0.0f),
				   const float angle = 0.0f,
				   const glm::vec3& direction = glm::vec3(1.0f, 0.0f, 0.0f),
				   const glm::vec3& scale = glm::vec3(1.0f),
				   const float speed = 0.0f)
			: position(position), angle(angle), direction(direction), scale(scale), speed(speed) {
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

		//Constructor
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