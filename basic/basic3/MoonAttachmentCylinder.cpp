/*
Represents the cylinders on the planet support poles that the moon support poles attach to
*/

#include "wrapper_glfw.h"
#include "glm/gtc/matrix_transform.hpp"
#include "MoonAttachmentCylinder.h"
#include "Cylinder.h"
#include <iostream>
#include <vector>
 
MoonAttachmentCylinder::MoonAttachmentCylinder(GLuint modelId, glm::vec3 startPosition, glm::vec3 cylinderScale, GLfloat startSunRotation, GLfloat sunOrbitSpeed, GLfloat startPlanetRotation, GLfloat planetOrbitSpeed, GLuint textureID) : Cylinder(modelId, startPosition, cylinderScale, textureID)
{
	sun_rotation_angle = startSunRotation;
	sun_orbit_speed = sunOrbitSpeed;
	planet_orbit_speed = planetOrbitSpeed;
	planet_rotation_angle = startPlanetRotation;
}
//Renders and rotates the moon attachment cylinder
void MoonAttachmentCylinder::Render()
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::rotate(model, sun_rotation_angle, glm::vec3(0, 1, 0));//rotate around the sun
	model = glm::translate(model, position);
	model = glm::rotate(model, planet_rotation_angle, glm::vec3(0, 1, 0));//rotate around the planet
	model = glm::scale(model, scale);

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	DrawCylinder();
	sun_rotation_angle += sun_orbit_speed;
	planet_rotation_angle += planet_orbit_speed;
}
//Sets the rotation speed of the moon attachment cylinder
void MoonAttachmentCylinder::SetRotationSpeed(GLfloat sunRotationSpeed, GLfloat planetRotationSpeed)
{
	sun_orbit_speed = sunRotationSpeed;
	planet_orbit_speed = planetRotationSpeed;
}