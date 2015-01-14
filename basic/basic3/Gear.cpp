/*
Represents a gear in the scene
*/

#include "wrapper_glfw.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Gear.h"
#include <iostream>
#include <vector>

Gear::Gear(GLuint modelId, glm::vec3 startPosition, glm::vec3 gearScale, GLfloat rotationSpeed, GLuint textureID)
{
	model_id = modelId;
	position = startPosition;
	scale = gearScale;
	texture_id = textureID;
	rotation = 0;
	rotation_speed = rotationSpeed;
	Initialise(50);
}
//Initialises the gear with vertex positions, normals and a texture
//Triangle count is the number of triangles in each of the two gear faces
void Gear::Initialise(GLuint triangleCount)
{
	//Create the 2 gear faces and the sides of the gear
	CreateGearFaces(triangleCount, 0.5f);
	CreateSides(triangleCount, 0.5f);

	GLuint num_vertices = (pVertices.size() / 3);

	int single_circle_vertex_part_count = (pVertices.size() + 6) / 4;
	int start_of_side_vertices = pVertices.size() / 2;
	//Assign the triangle strip indices
	for (int i = start_of_side_vertices + 1; i < start_of_side_vertices + single_circle_vertex_part_count; i++)
	{
		pIndices.push_back((i - 3 + single_circle_vertex_part_count) / 3);
		pIndices.push_back(i / 3);
	}

	glGenBuffers(1, &position_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* pVertices.size(), &pVertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normals_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normals_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pNormals.size() * sizeof(GLfloat), &pNormals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &texture_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pTexCoords.size() * sizeof(GLfloat), &pTexCoords[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndices.size() * sizeof(GLuint), &pIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Adds a vertex to the gear
void Gear::AddVertex(GLfloat x, GLfloat y, GLfloat z)
{
	pVertices.push_back(x);
	pVertices.push_back(y);
	pVertices.push_back(z);
}

//Adds a normal to the gear.
void Gear::AddNormal(GLfloat x, GLfloat y, GLfloat z)
{
	pNormals.push_back(x);
	pNormals.push_back(y);
	pNormals.push_back(z);
}

//Creates the vertices and normals used for the flat faces of the gear
void Gear::CreateGearFaces(GLuint triangles, GLfloat height)
{
	GLfloat half_height = height / 2;
	//Define the central vertex
	AddVertex(0, half_height, 0);
	//Assign a normal to the central vertex
	AddNormal(0, 1, 0);

	pTexCoords.push_back(0.5);
	pTexCoords.push_back(0.5);

	int start = pVertices.size();
	const float DEG2RAD = 3.14159 / 180;
	GLuint angle_step = 360 / triangles - 1;
#pragma region Top face
	//Top flat face
	for (int angle = angle_step; angle <= 360; angle += angle_step)
	{
		GLfloat rad_angle = DEG2RAD * angle;
		//http://mathworld.wolfram.com/GearCurve.html Gear parametric curve
		float r = 1 + (0.1 * tanh(10 * sin(12 * rad_angle)));
		GLfloat x = r * cos(rad_angle);
		GLfloat z = r  * sin(rad_angle);

		AddVertex(x, half_height, z);

		pTexCoords.push_back((x * 0.5) + 0.5);
		pTexCoords.push_back((z * 0.5) + 0.5);//http://stackoverflow.com/questions/8762826/texture-mapping-a-circle-made-using-gl-polygon

		//Assign 'up' normals to each of the face vertices
		AddNormal(0, 1, 0);
	}
	//Connect the last triangle fan to the first to complete the circle
	AddVertex(pVertices[start], pVertices[start + 1], pVertices[start + 2]);
	pTexCoords.push_back((pVertices[start] * 0.5) + 0.5);
	pTexCoords.push_back((pVertices[start + 2] * 0.5) + 0.5);
	//Assign a normal to the final triangle
	AddNormal(0, 1, 0);
#pragma endregion
#pragma region bottom face
	AddVertex(0, -half_height, 0);
	//Assign a normal to the central vertex
	AddNormal(0, -1, 0);

	pTexCoords.push_back(0.5);
	pTexCoords.push_back(0.5);

	start = pVertices.size();
	//Bottom flat face
	for (int angle = angle_step; angle <= 360; angle += angle_step)
	{
		GLfloat rad_angle = DEG2RAD * angle;
		//http://mathworld.wolfram.com/GearCurve.html Gear parametric curve
		float r = 1 + (0.1 * tanh(10 * sin(12 * rad_angle)));
		GLfloat x = r * cos(rad_angle);
		GLfloat z = r  * sin(rad_angle);

		AddVertex(x, -half_height, z);

		pTexCoords.push_back((x * 0.5) + 0.5);
		pTexCoords.push_back((z * 0.5) + 0.5);//http://stackoverflow.com/questions/8762826/texture-mapping-a-circle-made-using-gl-polygon

		//Assign 'up' normals to each of the face vertices
		AddNormal(0, -1, 0);
	}
	//Connect the last triangle fan to the first to complete the circle
	AddVertex(pVertices[start], pVertices[start + 1], pVertices[start + 2]);
	pTexCoords.push_back((pVertices[start] * 0.5) + 0.5);
	pTexCoords.push_back((pVertices[start + 2] * 0.5) + 0.5);
	//Assign a normal to the final triangle
	AddNormal(0, -1, 0);
#pragma endregion
}

//Creates the vertices and normals used for the sides of the gear
void Gear::CreateSides(GLuint triangles, GLfloat height)
{
	GLfloat half_height = height / 2;
	pTexCoords.push_back(0);
	pTexCoords.push_back(1);
	int start = pVertices.size();
	const float DEG2RAD = 3.14159 / 180;
	GLuint angle_step = 360 / triangles - 1;
#pragma region Top face
	//Top vertices
	for (int angle = angle_step; angle <= 360; angle += angle_step)
	{
		GLfloat rad_angle = DEG2RAD * angle;
		//http://mathworld.wolfram.com/GearCurve.html Gear parametric curve
		float r = 1 + (0.1 * tanh(10 * sin(12 * rad_angle)));
		GLfloat x = r * cos(rad_angle);
		GLfloat z = r  * sin(rad_angle);

		AddVertex(x, half_height, z);
		pTexCoords.push_back(rad_angle);
		pTexCoords.push_back(1);
		//Assign a side normal to the vertex
		AddNormal(x, 0, z);
	}
	//Connect the last triangle fan to the first to complete the circle
	AddVertex(pVertices[start], pVertices[start + 1], pVertices[start + 2]);
	//Assign a normal to the final triangle
	AddNormal(pVertices[start], 0, pVertices[start + 2]);
#pragma endregion
#pragma region bottom face
	pTexCoords.push_back(0);
	pTexCoords.push_back(0);
	start = pVertices.size();
	//Bottom flat face
	for (int angle = angle_step; angle <= 360; angle += angle_step)
	{
		GLfloat rad_angle = DEG2RAD * angle;
		//http://mathworld.wolfram.com/GearCurve.html Gear parametric curve
		float r = 1 + (0.1 * tanh(10 * sin(12 * rad_angle)));
		GLfloat x = r * cos(rad_angle);
		GLfloat z = r  * sin(rad_angle);

		AddVertex(x, -half_height, z);
		pTexCoords.push_back(rad_angle);
		pTexCoords.push_back(0);
		//Assign a side normal to the vertex
		AddNormal(x, 0, z);
	}
	//Connect the last triangle fan to the first to complete the circle
	AddVertex(pVertices[start], pVertices[start + 1], pVertices[start + 2]);
	//Assign a normal to the final triangle
	AddNormal(pVertices[start], 0, pVertices[start + 2]);
#pragma endregion
}

//Renders, scales and translates the cylinder to its position
void Gear::Render()
{
	//Bind the gear's texture
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(position));//Translate the gear to its position
	model = glm::rotate(model, rotation, glm::vec3(0, 1, 0));//Rotate in the y axis
	model = glm::scale(model, scale);

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_FAN, 0, pVertices.size() / 12 + 1);//Draws the top flat face of the gear
	glDrawArrays(GL_TRIANGLE_FAN, pVertices.size() / 12 + 1, pVertices.size() / 12 + 1);//Draws the bottom flat face of the gear
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glDrawElements(GL_TRIANGLE_STRIP, pIndices.size(), GL_UNSIGNED_INT, (GLvoid*)(0));//Draws the triangle strips for the sides of the gear

	rotation += rotation_speed;
}
//Sets the rotation speed for the gear
void Gear::SetRotationSpeed(GLfloat newSpeed)
{
	rotation_speed = newSpeed;
}