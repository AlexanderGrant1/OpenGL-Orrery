/*
A pole used to hold up a planet
*/

#include "wrapper_glfw.h"
#include "glm/gtc/matrix_transform.hpp"
#include "PlanetSupportPole.h"
#include <iostream>
#include <vector>

PlanetSupportPole::PlanetSupportPole(GLuint modelId, glm::vec3 startPosition, glm::vec3 cylinderScale, GLfloat rotationSpeed, GLfloat startRotation, bool horizontal, GLuint textureID) : Cylinder(modelId, startPosition, cylinderScale, textureID)
{
	model_id = modelId;
	position = startPosition;
	scale = cylinderScale;
	rotation_speed = rotationSpeed;
	rotation = startRotation;
	is_horizontal = horizontal;
}

//Renders and rotates a planet support pole
void PlanetSupportPole::Render()
{

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, rotation, glm::vec3(0, 1, 0));//Rotates the pole around the origin
	model = glm::translate(model, position);

	if (is_horizontal)
		model = glm::rotate(model, 90.f, glm::vec3(1,0,0));//if it's a horizontal pole rotate 90 degrees, default is vertical

	model = glm::scale(model, scale);

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	DrawCylinder();
	rotation += rotation_speed;
}

//Sets the speed at which the support pole orbits the sun
void PlanetSupportPole::SetRotationSpeed(GLfloat rotationSpeed)
{
	rotation_speed = rotationSpeed;
}