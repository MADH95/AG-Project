#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include "Input.h"
#include "KeyCode.h"
#include "MouseCode.h"

namespace Spoonity {

	//Abstraction for possible directions of movement
	enum class Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class Actor : public GameObject
	{

	//Member variables
	public:
		Camera* _Camera;

	protected:
		Model _Model;

	//Fuctions
	public:

		//Constructor
		Actor(const ObjectData& data,
			  Camera* camera,
			  const std::string& modelPath = "",
			  const Shader&	shader = Shader()
		);

		//Destructor
		virtual ~Actor();

		//Render the object
		virtual void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) = 0;

		//Update the object
		virtual void update(float& deltaTime) = 0;
	};
}