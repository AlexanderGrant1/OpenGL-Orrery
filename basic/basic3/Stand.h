#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
class Stand
{
protected:
	std::vector<GLfloat> pVertices;
	std::vector<GLuint> pIndices;
	std::vector<GLfloat> pNormals;
	glm::vec3 position;
	glm::vec3 scale;
	GLfloat rotation;
	GLuint model_id, position_buffer_object, element_buffer, normals_buffer_object, texture_buffer_object, texture_id;
public:
	Stand::Stand(GLuint modelId, glm::vec3 startPosition, glm::vec3 standScale, GLuint textureID);
	void Render();
};