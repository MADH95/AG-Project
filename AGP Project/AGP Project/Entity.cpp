#include "Entity.h"
#include <iostream>

namespace Spoonity {

	Entity::Entity(const ObjectData& data,
				   const std::string& modelPath,
				   const Shader& shader)
		: GameObject(data, shader), _Model(Model(modelPath))
	{
		
	}

	void Entity::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
	{
		if (_IsEnabled)
		{
			_Shader.use();
			_Shader.setMat4("projection", projection);
			_Shader.setMat4("view", view);

			glm::vec3 lookPos = _Data.position + _Data.direction;

			model = glm::mat4(1.0f);
			model = glm::translate(model, _Data.position);
			model = glm::rotate(model, _Data.angle, _Data.direction);
			model = glm::scale(model, _Data.scale);

			_Model.draw(_Shader, &model);
		}
	}

	void Entity::update(float& deltaTime)
	{
	}
}