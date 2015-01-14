/*
Represents a pole used to support a planet in the scene
*/

#include "wrapper_glfw.h"
#include "glm/gtc/matrix_transform.hpp"
#include "MoonSupportPole.h"
#include <iostream>
#include <vector>

MoonSupportPole::MoonSupportPole(GLuint modelId, glm::vec3 startPosition, glm::vec3 moonLocation, glm::vec3 cylinderScale, GLfloat sunOrbitSpeed, GLfloat planetOrbitSpeed, GLfloat startPlanetRotation, GLfloat startSunRotation, bool horizontal, GLuint textureID) : Cylinder(modelId, startPosition, cylinderScale, textureID)
{
	model_id = modelId;
	position = startPosition;
	scale = cylinderScale;
	sun_orbit_speed = sunOrbitSpeed;
	planet_orbit_speed = planetOrbitSpeed;
	planet_rotation = startPlanetRotation;
	sun_rotation = startSunRotation;
	is_horizontal = horizontal;
	rotation_point = moonLocation;
}

//Renders the moon support pole and performs any necessary rotations and translations
void MoonSupportPole::Render()
{
	//Rotation is done based on 2 pivots here.  The first pivot is the sun which is the same as before.
	//With the planet rotation i took the difference between the support pole's position and the rotation point
	//and then translated to that point and rotated. I then translated the pole back to the origin and then to the position
	//for the sun's rotation
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 dist = position - rotation_point;//Distance between the support pole's position and the planet's position used for rotating around a planet
	model = glm::rotate(model, sun_rotation, glm::vec3(0, 1, 0));//Rotate the planet around the sun
	model = glm::translate(model, position);//Translate the planet to its position
	model = glm::translate(model, -dist);//These next 3 lines are used for rotating around the planet
	model = glm::rotate(model, planet_rotation, glm::vec3(0, 1, 0));
	model = glm::translate(model, dist);

	if (is_horizontal)
		model = glm::rotate(model, 90.f, glm::vec3(1, 0, 0));//If its a horizontal pole rotate it 90 degrees

	model = glm::scale(model, scale);

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	DrawCylinder();
	planet_rotation += planet_orbit_speed;
	sun_rotation += sun_orbit_speed;
}

//Sets the moon orbit speed and planet orbit speed
void MoonSupportPole::SetOrbitSpeeds(GLfloat sunOrbitSpeed, GLfloat planetOrbitSpeed)
{
	sun_orbit_speed = sunOrbitSpeed;
	planet_orbit_speed = planetOrbitSpeed;
}