#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Cylinder.h"
class BaseCylinder : Cylinder
{
private:
	GLfloat rotation_angle;
	GLfloat rotation_speed;
public:
	BaseCylinder::BaseCylinder(GLuint modelId, glm::vec3 startPosition, glm::vec3 cylinderScale, GLfloat rotationSpeed, GLuint textureID);
	void Render();
	void SetRotationSpeed(GLfloat rotationSpeed);
};