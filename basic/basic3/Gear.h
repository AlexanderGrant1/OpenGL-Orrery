#pragma once

#include "wrapper_glfw.h"

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
class Gear
{
private:
	std::vector<GLfloat> pVertices;
	std::vector<GLuint> pIndices;
	std::vector<GLfloat> pNormals;
	std::vector<GLfloat> pTexCoords;
	glm::vec3 position;
	glm::vec3 scale;
	GLfloat rotation;
	GLfloat rotation_speed;
	GLuint model_id, position_buffer_object,  element_buffer, normals_buffer_object, texture_buffer_object, texture_id;
	void AddVertex(GLfloat x, GLfloat y, GLfloat z);
	void AddNormal(GLfloat x, GLfloat y, GLfloat z);
	void CreateSides(GLuint triangles, GLfloat height);
	void Initialise(GLuint triangleCount);
	void CreateGearFaces(GLuint triangles, GLfloat height);
public:
	Gear::Gear(GLuint modelId, glm::vec3 startPosition, glm::vec3 gearScale, GLfloat rotationSpeed, GLuint textureID);
	void SetRotationSpeed(GLfloat newSpeed);
	void Render();
};