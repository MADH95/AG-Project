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
}