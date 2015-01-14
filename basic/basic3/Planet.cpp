/*
Represents a planet in the scene
*/

#include "Planet.h"
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

Planet::Planet(GLuint modelId, glm::vec3 startPosition, glm::vec3 planetScale, GLfloat startRotation, GLfloat rotationSpeed, GLuint textureID) : Sphere(modelId, startPosition, planetScale, textureID)
{
	model_id = modelId;
	position = startPosition;
	scale = planetScale;
	rotation = startRotation;
	rotation_speed = rotationSpeed;
}
//Renders and rotates a planet
void Planet::Render()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, rotation, glm::vec3(0, 1, 0));//Rotate the planet around the origin
	model = glm::translate(model, position);//Move the planet to its position
	model = glm::rotate(model, rotation, glm::vec3(0, 1, 0));//Rotate the planet
	model = glm::scale(model, scale);//Scale the planet to its scale
	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	DrawSphere();
	rotation += rotation_speed;
}

//Sets the orbit speed of the planet
void Planet::SetRotationSpeed(GLfloat rotationSpeed)
{
	rotation_speed = rotationSpeed;
}