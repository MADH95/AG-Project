#include "Player.h"

//Constructor
Player::Player(const Spoonity::ObjectData& data,
			   const std::string&		   modelPath)
	: Actor(data, new Spoonity::Camera(data.position, data.direction), modelPath)
{
	_Data.position = glm::vec3(0.0f, 0.5f, 0.0f);
	_Camera->_Position = _Data.position + glm::vec3(0.0f, 0.2f, 0.0f);

	_Data.angle = -90.0f;
	_Camera->_Yaw = _Data.angle;
	
	_Data.direction = _Camera->_Front;

	_Data.scale = glm::vec3(1.0f);
	_Data.speed = 2.0f;

	_Camera->updateCameraVectors();

	_FirstMouse = true;
	_LastPos = glm::vec2(0.0f);
}

//Render the player Model
void Player::draw(const Spoonity::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model) 
{
	if (_IsEnabled)
	{
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, _Data.position);
		model = glm::rotate(model, glm::radians(_Data.angle), _Data.direction);
		model = glm::scale(model, _Data.scale);

		_Model.draw(shader, model);
	}
}

//Update the player
void Player::update(float& deltaTime)
{
	processInput(deltaTime);
}

//Process the input for player controls
void Player::processInput(float& deltaTime)
{
	using namespace Spoonity;

	//Escape closes the window
	if (Input::isKeyPressed(KeyCode::Escape))
		Input::closeWindow();

	//Temporary variables
	float velocity = _Data.speed * deltaTime;
	glm::vec3 front = normalize(glm::vec3(_Data.direction.x, 0.0f, _Data.direction.z));
	glm::vec3& right = _Camera->_Right;

	//Left shift is sprint key
	if (Input::isKeyPressed(KeyCode::LeftShift))
		velocity *= 1.6f;

	//Set the new position of the camera based on the keys W, A, S, & D
	if (Input::isKeyPressed(KeyCode::W))
		_Camera->_Position += front * velocity;
	if (Input::isKeyPressed(KeyCode::S))
		_Camera->_Position -= front * velocity;
	if (Input::isKeyPressed(KeyCode::D))
		_Camera->_Position += right * velocity;
	if (Input::isKeyPressed(KeyCode::A))
		_Camera->_Position -= right * velocity;

	/*
	//Flight controls
	if (Input::isKeyPressed(KeyCode::Space))
		_Camera->_Position += _Camera->_WorldUp * velocity;
	if (Input::isKeyPressed(KeyCode::LeftControl))
		_Camera->_Position -= _Camera->_WorldUp * velocity;

	//Clamp Height
	if (_Camera->_Position.y < 0.7f)
		_Camera->_Position.y = 0.7f;
	*/

	//Update the player position based on camera position
	_Data.position = _Camera->_Position - glm::vec3(0.0f, 0.2f, 0.0f);

	//Print player position when mouse button is pressed
	if (Input::isButtonPressed(MouseCode::LeftButton))
		std::cout << "(" << _Data.position.x << ", " << _Data.position.y << ", " << _Data.position.z << ")" << std::endl;

	glm::vec2 mousePosition = Input::getCursorPos();

	if (_FirstMouse)
	{
		_LastPos = mousePosition;
		_FirstMouse = false;
	}

	float xOffset = mousePosition.x - _LastPos.x;
	float yOffset = _LastPos.y - mousePosition.y; //Reversed since y-coordinates go from bottom to top

	_LastPos = mousePosition;

	xOffset *= 0.1f;
	yOffset *= 0.1f;

	_Camera->_Yaw += xOffset;
	_Camera->_Pitch += yOffset;

	if (_Camera->_Pitch > 89.0f)
		_Camera->_Pitch = 89.0f;
	if (_Camera->_Pitch < -89.0f)
		_Camera->_Pitch = -89.0f;

	_Camera->updateCameraVectors();

	_Data.direction = _Camera->_Front;
}