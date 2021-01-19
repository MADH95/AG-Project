#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Input.h"

namespace Spoonity {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Window", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	//A wrapper class for the GLFWwindow creation and manipulation
	class Window
	{

	//Member variables
	private:
		GLFWwindow* _Instance; //The GLFWwindow instance

		WindowProps _Properties; //Window Properties

	//Functions
	public:

		//Constructor
		Window(WindowProps properties);

		//Destructor
		~Window();

		//Function to get instance
		GLFWwindow* getInstance() const;

		//Function to get width
		unsigned int getWidth() const;

		//Function to get height
		unsigned int getHeight() const;

		void close() const;
	};
}