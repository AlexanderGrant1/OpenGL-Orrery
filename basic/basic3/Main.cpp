/*
 Assignment 1 - Alexander Grant
 November 2014
*/

/* Link to static libraries, could define these as linker inputs in the project settings instead
if you prefer */
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

/* Include the header to the GLFW wrapper class which
   also includes the OpenGL extension initialisation*/
#include "wrapper_glfw.h"
#include <iostream>

#include "Sun.h"
#include "Cylinder.h"
#include "BaseCylinder.h"
#include "Gear.h"
#include "Planet.h"
#include "PlanetSupportPole.h"
#include "MoonAttachmentCylinder.h"
#include "Moon.h"
#include "MoonSupportPole.h"
#include "Skybox.h"
#include "TextureLoader.h"
#include "Camera.h"
#include "Stand.h"
/* Include GLM core and matrix extensions*/
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

/* Define buffer object indices */
GLuint elementbuffer;

GLuint program;		/* Identifier for the shader prgoram */
GLuint vao;			/* Vertex array (Containor) object. This is the index of the VAO that will be the container for
					   our buffer objects */

GLfloat light_x, light_y, light_z;

/* Uniforms*/
GLuint modelID, viewID, projectionID, lightposID, normalmatrixID, applyLightingID;

BaseCylinder* base_cylinder;
BaseCylinder* fifth_cylinder;
BaseCylinder* fourth_cylinder;
BaseCylinder* intermediate1_cylinder;
BaseCylinder* mars_base_cylinder;
BaseCylinder* intermediate2_cylinder;
BaseCylinder* earth_base_cylinder;
BaseCylinder* intermediate3_cylinder;
BaseCylinder* venus_base_cylinder;
BaseCylinder* intermediate4_cylinder;
BaseCylinder* mercury_base_cylinder;
BaseCylinder* intermediate5_cylinder;

Planet* mercury;
Planet* venus;
Planet* earth;
Planet* mars;

Moon* earth_moon;
Moon* mars_moon1;
Moon* mars_moon2;

PlanetSupportPole* mercury_vertical_pole;
PlanetSupportPole* mercury_horizontal_pole;

PlanetSupportPole* venus_vertical_pole;
PlanetSupportPole* venus_horizontal_pole;

PlanetSupportPole* earth_vertical_pole;
PlanetSupportPole* earth_horizontal_pole;

PlanetSupportPole* mars_vertical_pole;
PlanetSupportPole* mars_horizontal_pole;

MoonAttachmentCylinder* earth_moon_attachment;
MoonSupportPole* earth_moon_horizontal_pole;
MoonSupportPole* earth_moon_vertical_pole;

MoonAttachmentCylinder* mars_moon1_attachment;
MoonSupportPole* mars_moon1_horizontal_pole;
MoonSupportPole* mars_moon1_vertical_pole;

MoonAttachmentCylinder* mars_moon2_attachment;
MoonSupportPole* mars_moon2_horizontal_pole;
MoonSupportPole* mars_moon2_vertical_pole;

Skybox* skybox;

Stand* stand1;
Stand* stand2;
Stand* stand3;

GLfloat mercury_speed_multiplier = 10.f;
GLfloat venus_speed_multiplier = 6.f;
GLfloat earth_speed_multiplier = 2.f;
GLfloat mars_speed_multiplier = 1.f;
GLfloat earth_moon_speed_multiplier = 15.f;
GLfloat mars_moon1_speed_multiplier = 20.f;
GLfloat mars_moon2_speed_multiplier = 15.f;

Sun* sun;

Gear* gear;

GLfloat orrery_speed = 0.005f;

Camera* camera;
/*
This function is called before entering the main rendering loop.
Use it for all your initialisation stuff
*/
void init(GLWrapper *glw)
{

	light_x = 0; light_y = 1.44f; light_z = 0;

	// Generate index (name) for one vertex array object
	glGenVertexArrays(1, &vao);

	// Create the vertex array object and make it current
	glBindVertexArray(vao);

	/* Load and build the vertex and fragment shaders */
	try
	{
		program = glw->LoadShader("vertexshader.vert", "fragmentshader.frag");
	}
	catch (std::exception &e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		std::cin.ignore();
		exit(0);
	}

	TextureLoader textureLoader = TextureLoader(program);

	//Load in textures using the SOIL library
	GLuint skyboxTexture = textureLoader.Load("skybox.png");
	GLuint earthTexture = textureLoader.Load("earth.png");
	GLuint venusTexture = textureLoader.Load("venusmap.png");
	GLuint marsTexture = textureLoader.Load("marsmap.png");
	GLuint mercuryTexture = textureLoader.Load("mercurymap.png");
	GLuint moonTexture = textureLoader.Load("moonmap.png");
	GLuint metalTexture = textureLoader.Load("metal.png");
	GLuint sunTexture = textureLoader.Load("Sun.png");

	/* Define uniforms to send to vertex shader */
	modelID = glGetUniformLocation(program, "model");
	viewID = glGetUniformLocation(program, "view");
	projectionID = glGetUniformLocation(program, "projection");
	lightposID = glGetUniformLocation(program, "lightpos");
	normalmatrixID = glGetUniformLocation(program, "normalmatrix");
	applyLightingID = glGetUniformLocation(program, "applyLighting");
	//Orrery base setup
	base_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0, 0), glm::vec3(2, 0.3f, 2.f), 0.f, metalTexture);//large cylinder as the base
	fifth_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.15f, 0), glm::vec3(0.4, 0.02f, 0.4), 0.f, metalTexture);//Flat cylinder for aesthetics
	fourth_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.28f, 0), glm::vec3(0.15f, 0.25f, 0.15f), 0.f, metalTexture);//Base for orrery
	intermediate1_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.42f, 0), glm::vec3(0.10f, 0.07f, 0.10f), 0.f, metalTexture);//Intermediate
	mars_base_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.5f, 0), glm::vec3(0.15f, 0.10f, 0.15f), orrery_speed * mars_speed_multiplier, metalTexture);
	intermediate2_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.58f, 0), glm::vec3(0.10f, 0.07f, 0.10f), 0.f, metalTexture);//Intermediate
	earth_base_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.66f, 0), glm::vec3(0.15f, 0.10f, 0.15f), orrery_speed * earth_speed_multiplier, metalTexture);
	intermediate3_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.74f, 0), glm::vec3(0.10f, 0.07f, 0.10f), 0.f, metalTexture);//Intermediate
	venus_base_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.82f, 0), glm::vec3(0.15f, 0.10f, 0.15f), orrery_speed * venus_speed_multiplier, metalTexture);
	intermediate4_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.9f, 0), glm::vec3(0.10f, 0.07f, 0.10f), 0.f, metalTexture);//Intermediate
	mercury_base_cylinder = new BaseCylinder(modelID, glm::vec3(0, 0.98f, 0), glm::vec3(0.15f, 0.10f, 0.15f), orrery_speed * mercury_speed_multiplier, metalTexture);
	intermediate5_cylinder = new BaseCylinder(modelID, glm::vec3(0, 1.06f, 0), glm::vec3(0.07f, 0.11f, 0.07f), 0.f, metalTexture);//Intermediate
	//Sun setup
	sun = new Sun(modelID, glm::vec3(0, 1.44, 0), glm::vec3(0.33f, 0.33f, 0.33f), orrery_speed,sunTexture);
	//Mercury setup
	mercury = new Planet(modelID, glm::vec3(0, 1.35f, 0.6), glm::vec3(0.05f, 0.05f, 0.05f), 0.f, orrery_speed * mercury_speed_multiplier,mercuryTexture);
	mercury_vertical_pole = new PlanetSupportPole(modelID, glm::vec3(0, 1.16, 0.6), glm::vec3(0.01, 0.4, 0.01), orrery_speed * mercury_speed_multiplier, 0.f, false,metalTexture);
	mercury_horizontal_pole = new PlanetSupportPole(modelID, glm::vec3(0, 0.97, 0.3), glm::vec3(0.012, 0.6, 0.012), orrery_speed * mercury_speed_multiplier, 0.f, true, metalTexture);
	//Venus setup
	venus = new Planet(modelID, glm::vec3(0, 1.27f, 0.9), glm::vec3(0.07f, 0.07f, 0.07f), 270.f, orrery_speed * venus_speed_multiplier,venusTexture);
	venus_vertical_pole = new PlanetSupportPole(modelID, glm::vec3(0, 1, 0.9), glm::vec3(0.01, 0.4, 0.01), orrery_speed * venus_speed_multiplier, 270.f, false, metalTexture);
	venus_horizontal_pole = new PlanetSupportPole(modelID, glm::vec3(0, 0.81f, 0.45), glm::vec3(-0.012, 0.9, -0.012), orrery_speed * venus_speed_multiplier, 270.f, true, metalTexture);
	//Earth setup
	earth = new Planet(modelID, glm::vec3(0, 1.14f, 1.2), glm::vec3(0.1f, 0.1f, 0.1f), 90.f, orrery_speed * earth_speed_multiplier,earthTexture);
	earth_vertical_pole = new PlanetSupportPole(modelID, glm::vec3(0, 0.84, 1.2), glm::vec3(0.01, 0.4, 0.01), orrery_speed * earth_speed_multiplier, 90.f, false, metalTexture);
	earth_horizontal_pole = new PlanetSupportPole(modelID, glm::vec3(0, 0.65f, 0.6), glm::vec3(0.012, 1.2, 0.012), orrery_speed * earth_speed_multiplier, 90.f, true, metalTexture);
	//Earth moon setup
	earth_moon = new Moon(modelID, glm::vec3(0, 1.15f, 1.4), glm::vec3(0, 1.2f, 1.2), orrery_speed * earth_moon_speed_multiplier, orrery_speed * earth_speed_multiplier, 0.f, 90.f, moonTexture);
	earth_moon_attachment = new MoonAttachmentCylinder(modelID, glm::vec3(0, 0.9f, 1.2f), glm::vec3(0.03, 0.08, 0.03), 90.f, orrery_speed * earth_speed_multiplier, 0, orrery_speed * earth_moon_speed_multiplier, metalTexture);
	earth_moon_vertical_pole = new MoonSupportPole(modelID, glm::vec3(0, 1.01f, 1.4), glm::vec3(0, 0.9f, 1.2f), glm::vec3(0.01, 0.23, 0.01), orrery_speed * earth_speed_multiplier, orrery_speed * earth_moon_speed_multiplier, 0.f, 90.f, false, metalTexture);
	earth_moon_horizontal_pole = new MoonSupportPole(modelID, glm::vec3(0, 0.9f, 1.3), glm::vec3(0, 0.9f, 1.2f), glm::vec3(0.01, 0.20, 0.01), orrery_speed * earth_speed_multiplier, orrery_speed * earth_moon_speed_multiplier, 0.f, 90.f, true, metalTexture);
	//Mars setup
	mars = new Planet(modelID, glm::vec3(0, 1.2f, 1.8), glm::vec3(0.15f, 0.15f, 0.15f), 180.f, orrery_speed* mars_speed_multiplier,marsTexture);
	mars_vertical_pole = new PlanetSupportPole(modelID, glm::vec3(0, 0.80, 1.8), glm::vec3(0.01, 0.6, 0.01), orrery_speed * mars_speed_multiplier, 180.f, false, metalTexture);
	mars_horizontal_pole = new PlanetSupportPole(modelID, glm::vec3(0, 0.5f, 0.9), glm::vec3(0.012, 1.8, 0.012), orrery_speed * mars_speed_multiplier, 180.f, true, metalTexture);
	//Mars moon 1 setup
	mars_moon1 = new Moon(modelID, glm::vec3(0, 1.2f, 1.6f), glm::vec3(0, 1.2f, 1.8f), orrery_speed* mars_moon1_speed_multiplier, orrery_speed* mars_speed_multiplier, 0, 180.f,moonTexture);
	mars_moon1_attachment = new MoonAttachmentCylinder(modelID, glm::vec3(0, 0.9f, 1.8f), glm::vec3(0.03, 0.08, 0.03), 180.f, orrery_speed * mars_speed_multiplier, 0, orrery_speed* mars_moon1_speed_multiplier, metalTexture);
	mars_moon1_vertical_pole = new MoonSupportPole(modelID, glm::vec3(0, 1.03, 1.6f), glm::vec3(0, 1.2, 1.8), glm::vec3(0.01, 0.28, 0.01), orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon1_speed_multiplier, 0, 180.f, false, metalTexture);
	mars_moon1_horizontal_pole = new MoonSupportPole(modelID, glm::vec3(0, 0.90f, 1.7f), glm::vec3(0, 1.2f, 1.8), glm::vec3(-0.01, -0.20, -0.01), orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon1_speed_multiplier, 0, 180.f, true, metalTexture);
	//Mars moon 2 setup
	mars_moon2 = new Moon(modelID, glm::vec3(0, 1.2f, 1.45f), glm::vec3(0, 1.2f, 1.8f), orrery_speed* mars_moon2_speed_multiplier, orrery_speed * mars_speed_multiplier, 180.f, 180.f, moonTexture);
	mars_moon2_attachment = new MoonAttachmentCylinder(modelID, glm::vec3(0, 0.7f, 1.8f), glm::vec3(-0.03, -0.08, -0.03), 180.f, orrery_speed * mars_speed_multiplier, 0, orrery_speed * mars_speed_multiplier, metalTexture);
	mars_moon2_vertical_pole = new MoonSupportPole(modelID, glm::vec3(0, 0.96, 1.45), glm::vec3(0, 1.2f, 1.8f), glm::vec3(0.01, 0.53, 0.01), orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon2_speed_multiplier, 180.f, 180.f, false, metalTexture);
	mars_moon2_horizontal_pole = new MoonSupportPole(modelID, glm::vec3(0, 0.7f, 1.63), glm::vec3(0, 1.2f, 1.8f), glm::vec3(-0.01, -0.35, -0.01), orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon2_speed_multiplier, 180.f, 180.f, true, metalTexture);
	
	//Skybox setup
	skybox = new Skybox(skyboxTexture, modelID);
	//Underneath of the orrery
	stand1 = new Stand(modelID, glm::vec3(1, 0, 1), glm::vec3(1), metalTexture);
	stand2 = new Stand(modelID, glm::vec3(-1, 0, 0.8), glm::vec3(1), metalTexture);
	stand3 = new Stand(modelID, glm::vec3(0, 1, 1), glm::vec3(1), metalTexture);
	gear = new Gear(modelID, glm::vec3(0, -0.2, 0), glm::vec3(0.33, 0.33, 0.33), orrery_speed * 5, metalTexture);
	//Camera setup
	camera = new Camera(viewID, projectionID, glm::vec3(0, 3, 6), glm::vec3(0, 0.5, 0));
}

/* Called to update the display. Note that this function is called in the event loop in the wrapper
   class because we registered display as a callback function */
void display()
{
	int i = 9e6;
	/* Define the background colour */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Clear the colour and frame buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Enable depth test  */
	glEnable(GL_DEPTH_TEST);

	/* Make the compiled shader program current */
	glUseProgram(program);

	// Define the light position and transform by the view matrix
	glm::vec4 lightpos = camera->GetView() * glm::vec4(light_x,light_y,light_z, 1.0);

	camera->Update();
	glUniform4fv(lightposID, 1, glm::value_ptr(lightpos));

	glUniform1ui(applyLightingID, 0);
	//I want these to be displayed exactly the same way all the time which is why I render these without lighting
	sun->Render();
	skybox->Render();
	glUniform1ui(applyLightingID, 1);

	base_cylinder->Render();
	fifth_cylinder->Render();
	fourth_cylinder->Render();
	
	intermediate1_cylinder->Render();
	mercury_base_cylinder->Render();
	intermediate2_cylinder->Render();
	venus_base_cylinder->Render();
	intermediate3_cylinder->Render();
	earth_base_cylinder->Render();
	intermediate4_cylinder->Render();
	mars_base_cylinder->Render();
	intermediate5_cylinder->Render();

	mercury->Render();
	mercury_vertical_pole->Render();
	mercury_horizontal_pole->Render();
	
	venus->Render();
	venus_vertical_pole->Render();
	venus_horizontal_pole->Render();

	earth->Render();
	earth_vertical_pole->Render();
	earth_horizontal_pole->Render();

	earth_moon->Render();
	earth_moon_attachment->Render();
	earth_moon_vertical_pole->Render();
	earth_moon_horizontal_pole->Render();

	mars->Render();
	mars_vertical_pole->Render();
	mars_horizontal_pole->Render();

	mars_moon1->Render();
	mars_moon1_attachment->Render();
	mars_moon1_vertical_pole->Render();
	mars_moon1_horizontal_pole->Render();

	mars_moon2->Render();
	mars_moon2_attachment->Render();
	mars_moon2_vertical_pole->Render();
	mars_moon2_horizontal_pole->Render();

	stand1->Render();
	stand2->Render();
	stand3->Render();
	gear->Render();

	glUseProgram(0);

}
//Updates the rotation speeds of all of the parts of the orrery in order to simulate a speed increase/decrease
static void updateOrrerySpeed()
{
	sun->SetRotationSpeed(orrery_speed);
	gear->SetRotationSpeed(orrery_speed * 5);

	mars_moon1->SetOrbitSpeeds(orrery_speed * mars_speed_multiplier,orrery_speed*mars_moon1_speed_multiplier);
	mars_moon1_attachment->SetRotationSpeed(orrery_speed * mars_speed_multiplier, orrery_speed*mars_moon1_speed_multiplier);
	mars_moon1_vertical_pole->SetOrbitSpeeds(orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon1_speed_multiplier);
	mars_moon1_horizontal_pole->SetOrbitSpeeds(orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon1_speed_multiplier);

	mars_moon2->SetOrbitSpeeds(orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon2_speed_multiplier);
	mars_moon2_attachment->SetRotationSpeed(orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon2_speed_multiplier);
	mars_moon2_vertical_pole->SetOrbitSpeeds(orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon2_speed_multiplier);
	mars_moon2_horizontal_pole->SetOrbitSpeeds(orrery_speed * mars_speed_multiplier, orrery_speed * mars_moon2_speed_multiplier);

	mercury->SetRotationSpeed(orrery_speed * mercury_speed_multiplier);
	mercury_vertical_pole->SetRotationSpeed(orrery_speed * mercury_speed_multiplier);
	mercury_horizontal_pole->SetRotationSpeed(orrery_speed * mercury_speed_multiplier);
	mercury_base_cylinder->SetRotationSpeed(orrery_speed * mercury_speed_multiplier);

	venus->SetRotationSpeed(orrery_speed * venus_speed_multiplier);
	venus_vertical_pole->SetRotationSpeed(orrery_speed * venus_speed_multiplier);
	venus_horizontal_pole->SetRotationSpeed(orrery_speed * venus_speed_multiplier);
	venus_base_cylinder->SetRotationSpeed(orrery_speed * venus_speed_multiplier);

	earth->SetRotationSpeed(orrery_speed * earth_speed_multiplier);
	earth_vertical_pole->SetRotationSpeed(orrery_speed * earth_speed_multiplier);
	earth_horizontal_pole->SetRotationSpeed(orrery_speed * earth_speed_multiplier);
	earth_base_cylinder->SetRotationSpeed(orrery_speed * earth_speed_multiplier);

	earth_moon->SetOrbitSpeeds(orrery_speed * earth_speed_multiplier,orrery_speed * earth_moon_speed_multiplier);
	earth_moon_horizontal_pole->SetOrbitSpeeds(orrery_speed * earth_speed_multiplier, orrery_speed * earth_moon_speed_multiplier);
	earth_moon_vertical_pole->SetOrbitSpeeds(orrery_speed * earth_speed_multiplier, orrery_speed * earth_moon_speed_multiplier);
	earth_moon_attachment->SetRotationSpeed(orrery_speed * earth_speed_multiplier, orrery_speed * earth_moon_speed_multiplier);

	mars->SetRotationSpeed(orrery_speed * mars_speed_multiplier);
	mars_vertical_pole->SetRotationSpeed(orrery_speed * mars_speed_multiplier);
	mars_horizontal_pole->SetRotationSpeed(orrery_speed * mars_speed_multiplier);
	mars_base_cylinder->SetRotationSpeed(orrery_speed * mars_speed_multiplier);
}

/* Called whenever the window is resized. The new window size is given, in pixels. */
static void reshape(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	camera->SetAspectRatio(((float)w / 640.f*4.f) / ((float)h / 480.f*3.f));
}
/* change view angle, exit upon ESC */
static void keyCallback(GLFWwindow* window, int key, int s, int action, int mods)
{
	/* Enable this call if you want to disable key responses to a held down key*/

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == '=')
	{
		orrery_speed += 0.001;
		updateOrrerySpeed();
	}
	if (key == '-')
	{
		orrery_speed -= 0.001;
		updateOrrerySpeed();
	}

	if (key == 'H')
	{
		light_x -= 1.f;
	}
	if (key == 'U')
	{
		light_y += 1.f;
	}
	if (key == 'J')
	{
		light_y -= 1.f;
	}
	if (key == 'K')
	{
		light_x += 1.f;
	}

	if (key == 'W')
	{
		camera->MoveForward();
	}

	if (key == 'S')
	{
		camera->MoveBackward();
	}

	if (key == 'A')
	{
		camera->RotateLeft();
	}

	if (key == 'D')
	{
		camera->RotateRight();
	}

	if (key == ' ')
	{
		camera->MoveUp();
	}

	if (key == 'X')
	{
		camera->MoveDown();
	}
}



/* Entry point of program */
int main(int argc, char* argv[])
{
	GLWrapper *glw = new GLWrapper(1024, 768, "AC41001 Assignment 1 - Alexander Grant");;
	std::cout << "----- Orrery Controls -----" << std::endl;
	std::cout << "Increase speed: =" << std::endl;
	std::cout << "Decrease speed: -" << std::endl;
	std::cout << "----- Camera Controls -----" << std::endl;
	std::cout << "Zoom in: W" << std::endl;
	std::cout << "Zoom out: S" << std::endl;
	std::cout << "Rotate Left: A" << std::endl;
	std::cout << "Rotate Right: D" << std::endl;
	std::cout << "Pan up: Spacebar" << std::endl;
	std::cout << "Pan down: X" << std::endl;
	std::cout << "----- Light Controls -----" << std::endl;
	std::cout << "Move up: U" << std::endl;
	std::cout << "Move down: J" << std::endl;
	std::cout << "Move Left: H" << std::endl;
	std::cout << "Move Right: K" << std::endl;
	std::cout << std::endl;
	std::cout << "There are objects on the underside of the orrery which can be viewed by moving the light underneath the orrery by pressing 'J'" << std::endl;
	std::cout << std::endl;
	if (!ogl_LoadFunctions())
	{
		fprintf(stderr, "ogl_LoadFunctions() failed. Exiting\n");
		return 0;
	}

	glw->setRenderer(display);
	glw->setKeyCallback(keyCallback);
	glw->setReshapeCallback(reshape);
	init(glw);

	glw->eventLoop();

	delete(glw);
	return 0;
}