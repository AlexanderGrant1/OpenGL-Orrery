/*
Represents the stands located on the underside of the orrery
These stands take the shape of a pyramid.
I used your explanation in the lectures to calculate the vertex normals
*/

#include "Stand.h"
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

Stand::Stand(GLuint modelId, glm::vec3 startPosition, glm::vec3 standScale, GLuint textureID)
{
	position = startPosition;
	scale = standScale;
	model_id = modelId;

	//The vertex positions of the pyramid
	GLfloat vertex_positions[] = {
		0, 0, 0.5, 
		0.5f, 0, -0.5, 
		-0.5f, 0, -0.5f,
		0, 0, 0.5,
		0, -0.5, 0,
		0.5f, 0, -0.5,
		0.5f, 0, -0.5,
		0, -0.5, 0,
		-0.5f, 0, -0.5f,
		-0.5f, 0, -0.5f,
		0, -0.5, 0,
		0, 0, 0.5,
	};

	//Pre calculated flat shaded normals for the pyramid
	GLfloat vertex_normals[] =
	{
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0.5, -0.25, 0.25,
		0.5, -0.25, 0.25,
		0.5, -0.25, 0.25,
		0, -0.5, -0.5,
		0, -0.5, -0.5,
	 	0, -0.5, -0.5,
		-0.5, -0.25, 0.25,
		-0.5, -0.25, 0.25,
		-0.5, -0.25, 0.25,
	};
	//Texture mappings
	GLfloat texture_mappings[] = {
		0.5, 1,
		1, 0,
		0,0,
		0, 0,
		0.5, 1,
		1, 0,
		0, 0,
		0.5, 1,
		1, 0,
		0, 0,
		0.5, 1,
		1, 0,
	};

	glGenBuffers(1, &position_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), &vertex_positions[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normals_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), &vertex_normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &texture_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), &texture_mappings[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Scales, rotates and renders the pyramid
void Stand::Render()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation, glm::vec3(0, 1, 0));
	model = glm::scale(model, scale);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, 12);
}
