/*
This sphere is taken from your examples
Code for texturing the sphere taken from blackboard
*/

#include "Sphere.h"
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

#include "wrapper_glfw.h"
#include <iostream>

/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

Sphere::Sphere(GLuint modelId, glm::vec3 startPosition, glm::vec3 sphereScale, GLuint textureID)
{
	model_id = modelId;
	position = startPosition;
	scale = sphereScale;
	texture_id = textureID;
	numlats = 100;
	numlongs = 100;
	makeSphereVBO();
}
//Creates the sphere vertex buffer object
GLuint Sphere::makeSphereVBO()
{
	GLuint i, j;
	/* Calculate the number of vertices required in sphere */
	GLuint numvertices = 2 + ((numlats - 1) * numlongs);
	GLfloat* pVertices = new GLfloat[numvertices * 3];
	GLfloat* pTexCoords = new GLfloat[numvertices * 2];
	makeUnitSphere(pVertices, pTexCoords, numlats, numlongs);


	/* Generate the vertex buffer object */
	glGenBuffers(1, &position_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* numvertices * 3, pVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Store the normals in a buffer object */
	glGenBuffers(1, &normals_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* numvertices * 3, pVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	/* Calculate the number of indices in our index array and allocate memory for it */
	GLuint numindices = ((numlongs * 2) + 2) * (numlats - 1) + ((numlongs + 2) * 2);
	GLuint* pindices = new GLuint[numindices];

	// fill "indices" to define triangle strips
	GLuint index = 0;		// Current index

	// Define indices for the first triangle fan for one pole
	for (i = 0; i < numlongs + 1; i++)
	{
		pindices[index++] = i;
	}
	pindices[index++] = 1;	// Join last triangle in the triangle fan

	GLuint start = 1;		// Start index for each latitude row
	for (j = 0; j < numlats - 2; j++)
	{
		for (i = 0; i < numlongs; i++)
		{
			pindices[index++] = start + i;
			pindices[index++] = start + i + numlongs;
		}
		pindices[index++] = start; // close the triangle strip loop by going back to the first vertex in the loop
		pindices[index++] = start + numlongs; // close the triangle strip loop by going back to the first vertex in the loop

		start += numlongs;
	}

	// Define indices for the last triangle fan for the south pole region
	for (i = numvertices - 1; i > (numvertices - numlongs - 2); i--)
	{
		pindices[index++] = i;
	}
	pindices[index] = numvertices - 2;	// Tie up last triangle in fan

	// Generate a buffer for the indices
	glGenBuffers(1, &element_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numindices * sizeof(GLuint), pindices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &texCoords);
	glBindBuffer(GL_ARRAY_BUFFER, texCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* numvertices * 2, pTexCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete pindices;
	delete pVertices;
	return numvertices;
}

void Sphere::makeUnitSphere(GLfloat *pVertices, GLfloat *pTexCoords, GLuint numlats, GLuint numlongs)
{
	GLfloat DEG_TO_RADIANS = 3.141592f / 180.f;
	GLuint vnum = 0;
	GLfloat x, y, z, lat_radians, lon_radians;

	/* Define north pole */
	pVertices[0] = 0; pVertices[1] = 0; pVertices[2] = 1.f;
	pTexCoords[0] = 0;	pTexCoords[1] = 0;
	vnum++;

	GLfloat latstep = 180.f / numlats;
	GLfloat longstep = 360.f / numlongs;

	/* Define vertices along latitude lines */
	for (GLfloat lat = 90.f - latstep; lat > -90.f; lat -= latstep)
	{
		lat_radians = lat * DEG_TO_RADIANS;
		for (GLfloat lon = -180.f; lon < 180.f; lon += longstep)
		{
			lon_radians = lon * DEG_TO_RADIANS;

			x = cos(lat_radians) * cos(lon_radians);
			y = cos(lat_radians) * sin(lon_radians);
			z = sin(lat_radians);

			/* Define the vertex */
			pVertices[vnum * 3] = x; pVertices[vnum * 3 + 1] = y; pVertices[vnum * 3 + 2] = z;
			pTexCoords[vnum * 2 + 1] = (lat + 90.f) / 180.f;
			pTexCoords[vnum * 2] = (lon + 180.f) / 360.f;
			vnum++;
		}
	}
	/* Define south pole */
	pVertices[vnum * 3] = 0; pVertices[vnum * 3 + 1] = 0; pVertices[vnum * 3 + 2] = -1.f;
	pTexCoords[vnum * 2] = 1.f;	pTexCoords[vnum * 2] = 1.f;
}

//Renders, scales and translates the sphere to its position
void Sphere::Render()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);//scale equally in all axis

	glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
	DrawSphere();
}

/* Draws the sphere form the previously defined vertex and index buffers */
void Sphere::DrawSphere()
{
	glBindTexture(GL_TEXTURE_2D, texture_id);
	GLuint i;

	/* Draw the vertices as GL_POINTS */
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_object);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	/* Bind the sphere normals */
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normals_buffer_object);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, texCoords);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/* Bind the indexed vertex buffer */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);

	/* Draw the north pole regions as a triangle  */
	glDrawElements(GL_TRIANGLE_FAN, numlongs + 2, GL_UNSIGNED_INT, (GLvoid*)(0));

	/* Calculate offsets into the indexed array. Note that we multiply offsets by 4
	because it is a memory offset the indices are type GLuint which is 4-bytes */
	GLuint lat_offset_jump = (numlongs * 2) + 2;
	GLuint lat_offset_start = numlongs + 2;
	GLuint lat_offset_current = lat_offset_start * 4;

	/* Draw the triangle strips of latitudes */
	for (i = 0; i < numlats - 2; i++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, numlongs * 2 + 2, GL_UNSIGNED_INT, (GLvoid*)(lat_offset_current));
		lat_offset_current += (lat_offset_jump * 4);
	}
	/* Draw the south pole as a triangle fan */
	glDrawElements(GL_TRIANGLE_FAN, numlongs + 2, GL_UNSIGNED_INT, (GLvoid*)(lat_offset_current));
}
//Sets the position of the sphere
void Sphere::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position = glm::vec3(x, y, z);
}
