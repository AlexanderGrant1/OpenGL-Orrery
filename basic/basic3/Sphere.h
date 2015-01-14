#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
class Sphere
{
protected:
	GLuint model_id, position_buffer_object, element_buffer, normals_buffer_object, texture_buffer_object, numlats, numlongs, numspherevertices;
	GLuint texture_id, texCoords;
	glm::vec3 scale;
	glm::vec3 position;
	void DrawSphere();
private:
	void makeUnitSphere(GLfloat *pVertices, GLfloat *pTexCoords, GLuint numlats, GLuint numlongs);
	GLuint makeSphereVBO();
public:
	Sphere::Sphere(GLuint modelId, glm::vec3 startPosition, glm::vec3 sphereScale, GLuint textureID);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void Render();
};