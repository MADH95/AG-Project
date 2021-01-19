#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

using namespace glm;

class Transform
{
private:
	mat4 transformMatrix;
	
public:
	Transform();
	virtual ~Transform() {}

	void Translate(vec3& translation);
	void Scale(vec3& scaling);
	void Rotate(float angle, vec3 axis);

	vec2 getPosition();
	vec2 getScale();
	vec2 getOrientation();
	vec2 getUpDir();
	vec2 getLeftDir();

	mat3 localToWorldMatrix();
	mat3 worldToLocalMatrix();
};