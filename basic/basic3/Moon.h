#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Sphere.h"
class Moon : Sphere
{
private:
	GLfloat sun_rotation;
	GLfloat planet_rotation;
	GLfloat sun_orbit_speed;
	GLfloat planet_orbit_speed;
	glm::vec3 planet_location;
public:
	Moon::Moon(GLuint modelId, glm::vec3 startPosition, glm::vec3 planetLocation, GLfloat planetOrbitSpeed, GLfloat sunOrbitSpeed, GLfloat startPlanetRotation, GLfloat startSunRotation, GLuint textureID);
	void Render();
	void SetOrbitSpeeds(GLfloat sunOrbitSpeed, GLfloat moonOrbitSpeed);
};