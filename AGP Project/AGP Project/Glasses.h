#pragma once

#include "Entity.h"
#include "Renderer.h"

class Glasses : public Spoonity::Entity
{
	//Variables
public:

	Spoonity::Shader _PostProcessShader;

	//Functions
public:

	//Constructor
	Glasses(const Spoonity::ObjectData& data,
		const std::string& modelPath,
		const Spoonity::Shader& postProcessShader);

	void update(float& deltaTime) override;
};