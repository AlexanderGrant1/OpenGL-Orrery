#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Sphere.h"
class Planet : Sphere
{
private:
	GLfloat rotation;
	GLfloat rotation_speed;
public:
	Planet::Planet(GLuint modelId, glm::vec3 startPosition, glm::vec3 planetScale, GLfloat startRotation, GLfloat rotationSpeed, GLuint textureID);
	void Render();
	void SetRotationSpeed(GLfloat rotationSpeed);
};