/*
Represents one of the moons in the scene.
*/

#include "Moon.h"
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

Moon::Moon(GLuint modelId, glm::vec3 startPosition, glm::vec3 planetLocation, GLfloat planetOrbitSpeed, GLfloat sunOrbitSpeed, GLfloat startPlanetRotation, GLfloat startSunRotation, GLuint textureID) : Sphere(modelId, startPosition, glm::vec3(0.03, 0.03, 0.03), textureID)
{
	model_id = modelId;
	position = startPosition; 
	sun_rotation = startSunRotation;
	planet_rotation = startPlanetRotation;
	sun_orbit_speed = sunOrbitSpeed;
	planet_orbit_speed = planetOrbitSpeed;
	planet_location = planetLocation;
}
//Renders and translates the moon to its position and rotates it around the sun and planet
void Moon::Render()
{
	//Rotation is done based on 2 pivots here.  The first pivot is the sun which is the same as before.
	//With the planet rotation i took the difference between the support pole's position and the rotation point
	//and then translated to that point and rotated. I then translated the pole back to the origin and then to the position
	//for the sun's rotation
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 dist = position - planet_location;//Get the distance between the moon's position and the planet's position (used for rotating around the planet)
	model = glm::rotate(model, sun_rotation, glm::vec3(0, 1, 0));//The next 2 lines are used for rotating around the sun
	model = glm::translate(model, position);
	model = glm::translate(model, -dist);//These next 3 lines are used for rotating around the planet
	model = glm::rotate(model, planet_rotation, glm::vec3(0, 1, 0));
	model = glm::translate(model, dist);
	model = glm::scale(model, glm::vec3(0.03,0.03,0.03));//All moons are scaled to 0.03
	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	DrawSphere();
	sun_rotation += sun_orbit_speed;
	planet_rotation += planet_orbit_speed;
}

//Sets the sun and planet orbit speeds of the moon
void Moon::SetOrbitSpeeds(GLfloat sunOrbitSpeed, GLfloat planetOrbitSpeed)
{
	sun_orbit_speed = sunOrbitSpeed;
	planet_orbit_speed = planetOrbitSpeed;
}