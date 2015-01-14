#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Cylinder.h"
class MoonSupportPole : Cylinder
{
private:
	bool is_horizontal;
	GLfloat sun_orbit_speed = 0;
	GLfloat planet_orbit_speed;
	GLfloat planet_rotation;
	GLfloat sun_rotation;
	glm::vec3 rotation_point;
public:
	MoonSupportPole::MoonSupportPole(GLuint modelId, glm::vec3 startPosition, glm::vec3 moonLocation, glm::vec3 cylinderScale, GLfloat sunOrbitSpeed, GLfloat planetOrbitSpeed, GLfloat startPlanetRotation, GLfloat startSunRotation, bool horizontal, GLuint textureID);
	void Render();
	void SetOrbitSpeeds(GLfloat sunOrbitSpeed, GLfloat planetOrbitSpeed);
};