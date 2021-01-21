#include "Glasses.h"

Glasses::Glasses(const Spoonity::ObjectData& data,
				 const std::string& modelPath,
				 const Spoonity::Shader& postProcessShader)
	: Entity(data, modelPath), _PostProcessShader(postProcessShader)
{
}

void Glasses::update(float& deltaTime)
{
	//TODO: bobbing and rotating code
	static float timeSinceStart = 0.0f;
	static float startY = _Data.position.y;

	float rotateIncrement = 45.0f, amplitude = 0.1f, frequency = 0.2f;
	float tempY = startY;

	_Data.angle += rotateIncrement * deltaTime;

	timeSinceStart += deltaTime;

	tempY += glm::sin(glm::pi<float>() * timeSinceStart * frequency) * amplitude;

	_Data.position.y = tempY;
}