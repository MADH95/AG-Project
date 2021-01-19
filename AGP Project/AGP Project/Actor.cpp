#include "Actor.h"

namespace Spoonity {

	//Constructor
	Actor::Actor(const ObjectData& data,
				 Camera* camera,
				 const std::string& modelPath)
		: GameObject(data, true),
		_Model(modelPath == "" ? Model() : Model(modelPath)),
		_Camera(camera)
	{
	}

	//Destructor
	Actor::~Actor()
	{
		delete _Camera;
	}
}