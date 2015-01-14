/*
A skybox to enhance the scene.
Some reference was made to your texturing examples.
*/

#pragma import SOIL.lib
#include "Skybox.h"
#include "TextureLoader.h"
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>
#include "SOIL.h"
/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

Skybox::Skybox(GLuint skyboxTexture, GLuint modelId)
{
	model_id = modelId;
	texID = skyboxTexture;
	GLfloat vertexPositions[] =
	{
		0.75f, 0, -0.75f,
		-0.75f, 0, -0.75f,
		-0.75f, 0, 0.75f,
		0.75f, 0, 0.75f,

	};
	//Texture coordinates for the skybox
	GLfloat textureCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	glGenBuffers(1, &position_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenBuffers(1, &texture_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Basically uses the same coordinates for each face but with different rotations applied
void Skybox::Render()
{
	glBindTexture(GL_TEXTURE_2D, texID);
	//Top
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 7.5, 0));
	model = glm::scale(model, glm::vec3(10));
	
	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//Bottom
	model = glm::mat4(1.0f);
	model = glm::rotate(model, 180.f,glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 7.5, 0));
	model = glm::scale(model, glm::vec3(10));

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	//Side
	model = glm::mat4(1.0f);
	model = glm::rotate(model, 90.f, glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 7.5, 0));
	model = glm::scale(model, glm::vec3(10));

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	//Side
	model = glm::mat4(1.0f);
	model = glm::rotate(model, 270.f, glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 7.5, 0));
	model = glm::scale(model, glm::vec3(10));

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//Side
	model = glm::mat4(1.0f);
	model = glm::rotate(model, 90.f, glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0, 7.5, 0));
	model = glm::scale(model, glm::vec3(10));

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


	//Side
	model = glm::mat4(1.0f);
	model = glm::rotate(model, 270.f, glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0, 7.5, 0));
	model = glm::scale(model, glm::vec3(10));

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_object);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


}

