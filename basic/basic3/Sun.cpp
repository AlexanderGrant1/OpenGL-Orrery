/*
Represents the sun at the centre of the scene
*/

#include "Sun.h"
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

Sun::Sun(GLuint modelId, glm::vec3 startPosition, glm::vec3 sunScale, GLfloat rotationSpeed, GLuint textureID) : Sphere(modelId, startPosition, sunScale, textureID)
{
	position = startPosition;
	scale = sunScale;
	model_id = modelId;
	rotation = 0;
	rotation_speed = rotationSpeed;
}
//Renders, translates and rotates the sun
void Sun::Render()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation, glm::vec3(0, 1, 0));
	model = glm::scale(model, scale);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	DrawSphere();
	rotation += rotation_speed;
}
//Sets the rotation speed of the sun
void Sun::SetRotationSpeed(GLfloat rotationSpeed)
{
	rotation_speed = rotationSpeed;
}