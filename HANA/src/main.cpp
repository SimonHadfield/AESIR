#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

//#include"Texture.h"
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



// 3D vertices
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
GLuint indices[] =
{
	0, 2, 1,	// upper left triangle
	0, 3, 2,	// lower right triangle
};
*/


int main()
{
	//init glfw
	glfwInit();

	// tell glfw what version of opengl we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// using core profile (modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// settings
	const unsigned int window_width = 1280;//800;
	const unsigned int window_height = 720;//600;

	// create a glfw window
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "HANA", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // capture mouse
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// introduce window into current context
	glfwMakeContextCurrent(window);

	// load glad
	gladLoadGL();

	glEnable(GL_DEPTH_TEST); // to prevent faces behind others rendering infront
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);

	// specify the viewport of opengl in the window
	// goes from x = 0 -> 800 and y = 0 -> 800
	glViewport(0, 0, window_width, window_height);

	Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag");

	std::cout << "Shader ID: " << shaderProgram.ID << std::endl;

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	//EBO EBO1(indices, sizeof(indices));

	// links VBO to VAO
	//	VBO			GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset
	//  1			2			   3					 4			   5				 6
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	//VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));
	// Unbind to prevent modifying
	VAO1.Unbind();
	VBO1.Unbind();
	//EBO1.Unbind();


	// texture
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("res/textures/Logo.png", &widthImg, &heightImg, &numColCh, 0);

	if (!bytes)
	{
		std::cout << "Image failed to load" << std::endl;
		std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
	}

	else {
		std::cout << "Image loaded successfully!" << std::endl;
		std::cout << "Width: " << widthImg << " pixels" << std::endl;
		std::cout << "Height: " << heightImg << " pixels" << std::endl;
		std::cout << "Number of channels: " << numColCh << std::endl;

	}

	GLuint texture;
	glGenTextures(0, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	if (tex0Uni == -1)
		std::cout << "tex0Uni not found" << std::endl;
	
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);
	std::cout << "tex0Uni: " << tex0Uni << std::endl;

	
	
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

		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (GLfloat)glfwGetTime() * glm::radians(40.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); 
		projection = glm::perspective(glm::radians(fov), (float)window_width / (float)window_height, 0.1f, 100.0f);


		GLint modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		GLint viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		GLint projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	
		//			// location //no. matrices
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//std::cout << "glfwGetTime(): " << glfwGetTime() << std::endl;
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glBindTexture(GL_TEXTURE_2D, texture);
		VAO1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();

		prevTime = currentTime;
	}

	VAO1.Delete();
	VBO1.Delete();
	//EBO1.Delete();
	shaderProgram.Delete();
	glDeleteTextures(1, &texture);

	glfwDestroyWindow(window);
	glfwTerminate();

	std::cin.get();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) && (GLFW_CURSOR_DISABLED))
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) && (GLFW_CURSOR_NORMAL))
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) *
		cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) *
		cameraSpeed;

}

// mouse movement callback
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
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