#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Spoonity {

	class Shader
	{

		//Member Variables
	public:
		unsigned int _ID;

		//Functions
	public:

		//Constructor
		Shader();

		Shader(std::string const&& vertexPath, std::string const&& fragmentPath, std::string const&& geometryPath = "");

		//Use the shader
		void use() const;

		//Utility functions for setting shader values
		void setBool(const std::string& name, bool value) const;

		void setInt(const std::string& name, int value) const;

		void setFloat(const std::string& name, float value) const;

		void setVec2(const std::string& name, glm::vec2 value);

		void setVec3(const std::string& name, glm::vec3 value) const;

		void setVec4(const std::string& name, glm::vec4 value) const;

		void setMat2(const std::string& name, glm::mat2 value) const;

		void setMat3(const std::string& name, glm::mat3 value) const;

		void setMat4(const std::string& name, glm::mat4 value) const;

	private:

		//Check compilation errors for shader
		void checkCompileErrors(GLuint shader, std::string type) const;
	};
}