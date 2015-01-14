/*
Represents one of the cylinders that acts a base for the orrery
*/

#include "wrapper_glfw.h"
#include "glm/gtc/matrix_transform.hpp"
#include "BaseCylinder.h"
#include "Cylinder.h"
#include <iostream>
#include <vector>

BaseCylinder::BaseCylinder(GLuint modelId, glm::vec3 startPosition, glm::vec3 cylinderScale, GLfloat rotationSpeed, GLuint textureID) : Cylinder(modelId, startPosition, cylinderScale, textureID,10)
{
	rotation_angle = 0;
	rotation_speed = rotationSpeed;
}

//Renders, scales, rotates and translates the cylinder
void BaseCylinder::Render()
{
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(position));//Translate to the cylinder's position
	model = glm::rotate(model, rotation_angle, glm::vec3(0, 1, 0));//Rotate the cylinder
	model = glm::scale(model, scale);

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	DrawCylinder();
	rotation_angle += rotation_speed;
}

//Sets the rotation speed for the cylinder
void BaseCylinder::SetRotationSpeed(GLfloat rotationSpeed)
{
	rotation_speed = rotationSpeed;
}