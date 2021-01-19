#include "Window.h"

namespace Spoonity {

	//Constructor
	Window::Window(WindowProps properties)
		: _Properties(properties)
	{
		//GLFW: initialise and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_Instance = glfwCreateWindow(_Properties.Width, _Properties.Height, _Properties.Title.c_str(), NULL, NULL);

		if (_Instance == NULL)
		{
			glfwTerminate();
			throw "Failed to create GLFW window";
		}

		glfwMakeContextCurrent(_Instance);
		glfwSetFramebufferSizeCallback(_Instance, Input::framebufferSizeCallback);
		glfwSetScrollCallback(_Instance, Input::scrollCallback);

		//Tell GLFW to capture mouse
		glfwSetInputMode(_Instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		//Glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw "Failed to initialize GLAD";
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	//Function to get instance
	GLFWwindow* Window::getInstance() const
	{
		return _Instance;
	}

	//Function to get width
	unsigned int Window::getWidth() const
	{
		return _Properties.Width;
	}

	//Function to get height
	unsigned int Window::getHeight() const
	{
		return _Properties.Height;
	}
	void Window::close() const
	{
		glfwSetWindowShouldClose(_Instance, true);
	}
}