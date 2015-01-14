#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Cylinder.h"
class PlanetSupportPole : Cylinder
{
private:
	bool is_horizontal;
	GLfloat rotation_speed = 0;
	GLfloat rotation;
public:
	PlanetSupportPole::PlanetSupportPole(GLuint modelId, glm::vec3 startPosition, glm::vec3 cylinderScale, GLfloat rotationSpeed, GLfloat startRotation, bool horizontal, GLuint textureID);
	void Render();
	void SetRotationSpeed(GLfloat rotationSpeed);
};