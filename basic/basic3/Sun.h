#pragma once
#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Sphere.h"
class Sun : Sphere
{
private:
	glm::vec3 position;
	glm::vec3 scale;
	GLfloat rotation;
	GLfloat rotation_speed;
public:
	Sun::Sun(GLuint modelId, glm::vec3 startPosition, glm::vec3 sunScale, GLfloat rotationSpeed, GLuint textureID);
	void Render();
	void SetTexture(char* texturePath);
	void SetRotationSpeed(GLfloat rotationSpeed);
	void Rotate(GLfloat amount, glm::vec3& axis);
};