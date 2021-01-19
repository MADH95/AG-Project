#pragma once
#include "Actor.h"
#include "Camera.h"

class Player : public Spoonity::Actor
{
//Variables
private:
	//Used for mouse movement
	glm::vec2 _LastPos;
	bool _FirstMouse;

//Functions
public:

	//Constructor
	Player(const Spoonity::ObjectData& data,
		   const std::string& modelPath = ""
	);

	//Render the player Model
	void draw(const Spoonity::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;

	//Update the player
	void update(float& deltaTime) override;

	//Process the input for player controls
	void processInput(float& deltaTime);
};