#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include"Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// set up camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// delta time
GLfloat deltaTime = 0.0f;
GLfloat currentTime = 0.0f;
GLfloat prevTime = 0.0f;

// 3D vertices for cube (no colour)
GLfloat vertices[] =
{
	//  COORDINATES				// TEXTURE COORDINATES
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f

};

/*
// index buffer
GLuint indices[] = {};
*/

int main()
{
	glfwInit(); //initialize glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// assign opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					// assign "
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// using core profile

	// window size
	const unsigned int window_width = 1280;
	const unsigned int window_height = 720;

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "HANA", NULL, NULL);		// create a glfw window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);							// callback for resizing window
	glfwSetCursorPosCallback(window, mouse_callback);											// callback - mouseInputs
	glfwSetScrollCallback(window, scroll_callback);												// callback - scrollInput

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);								// capture mouse
	
	if (window == NULL)																			// Check GLFW window opens
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);					// introduce window into current context
	gladLoadGL();									// load glad


	//		-- GLOBAL SETTINGS
	glEnable(GL_DEPTH_TEST);						// Depth test for rendering order
	//glEnable(GL_CULL_FACE);
	glViewport(0, 0, window_width, window_height);	// specify the viewport in given window


	//		-- SHADERS
	Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag"); // create shader with vertexShader and fragmentShader
	VAO VAO1;										// create vertex array
	VAO1.Bind();									// bind vertexy array

	VBO VBO1(vertices, sizeof(vertices));			// create vertex buffer
	//EBO EBO1(indices, sizeof(indices));			// indices not currently needed

	//	link VBO to VAO
	//	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);							// link position vertices
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));	// link texture vertices
	
	// Unbind to prevent modifying
	VAO1.Unbind();
	VBO1.Unbind();
	//EBO1.Unbind();								// indices not currently needed

	// texture (create texture, bind and assign to uniform)
	Texture tex0("res/textures/Logo.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
	tex0.Bind();
	tex0.texUnit(shaderProgram, "tex0", 0);

	
	// main while loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.09f, 0.13f, 0.19f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();
		
		// set delta time
		currentTime = (GLfloat)glfwGetTime();
		deltaTime = currentTime - prevTime;

		// model, view, projection
		glm::mat4 model = glm::mat4(1.0f);			// init identity matrices
		glm::mat4 view = glm::mat4(1.0f);			// ''
		glm::mat4 projection = glm::mat4(1.0f);		// ''
		model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));			// set model to rotate in time
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);												// set view to camera
		projection = glm::perspective(glm::radians(fov), (float)window_width / (float)window_height, 0.1f, 100.0f);		// set projection to perspective 

		// get uniform locations 
		GLint modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		GLint viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		GLint projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	
		// 1 - uni location, 2 - no. of matrices, 3 - transpose, 4 - ptr
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));		// assign uniforms
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));			// ''
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));	//''

		tex0.Bind();
		VAO1.Bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); // show new rendered frame
		glfwPollEvents();

		prevTime = currentTime;
	}

	VAO1.Delete();
	VBO1.Delete();
	//EBO1.Delete();
	shaderProgram.Delete();
	tex0.Delete();
	//glDeleteTextures(1, &texture);

	glfwDestroyWindow(window);
	glfwTerminate();

	std::cin.get();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); // match viewport to current window size
}

void processInput(GLFWwindow* window)
{
	if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) && (GLFW_CURSOR_DISABLED))
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) or glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)				// move camera forward -	W / ARROW-UP
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) or glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)				// move camera backwards -	S / ARROW-DOWN
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) or glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)				// move camera left -		A / ARROW-LEFT
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) or glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)				// move camera right -		D / ARROW-RIGHT
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_E) or glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)				// move camera up -			E / SPACEBAR
		cameraPos += cameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) or glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)		// move camera down -		Q / LEFT-CTRL 
		cameraPos -= cameraUp * cameraSpeed;

}

// mouse movement callback
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse) // center mouse position
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

// mouse scroll wheel scroll callback 
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}