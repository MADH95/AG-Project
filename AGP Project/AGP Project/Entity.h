#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Model.h"

namespace Spoonity {

	class Entity : public GameObject
	{
	//Variables
	private:
		//Entities control their own model
		Model _Model;

	//Functions
	public:

		//Constructor
		Entity(const ObjectData& data,
			   const std::string& modelPath
		);

		//Render the object
		virtual void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;

		//Unused by skybox
		virtual void update(float& deltaTime) override;

	};
}