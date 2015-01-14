#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Cylinder.h"
class MoonAttachmentCylinder : Cylinder
{
private:
	GLfloat sun_rotation_angle;
	GLfloat sun_orbit_speed;
	GLfloat planet_orbit_speed;
	GLfloat planet_rotation_angle;
public:
	MoonAttachmentCylinder::MoonAttachmentCylinder(GLuint modelId, glm::vec3 startPosition, glm::vec3 cylinderScale, GLfloat startSunRotation, GLfloat sunRotationSpeed, GLfloat startPlanetRotation, GLfloat planetRotationSpeed, GLuint textureID);
	void Render();
	void SetRotationSpeed(GLfloat planetRotationSpeed, GLfloat sunRotationSpeed);
};