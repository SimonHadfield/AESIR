#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// create vertices
GLfloat vertices[] =
{
	//		COORDINATES				//	COLORS				// TEXTURE COORD
	-0.5f,  -0.5f, 0.0f,			1.0f, 0.0f,  0.0f,		 0.0f, 0.0f, // lower left corner
	-0.5f,   0.5f, 0.0f,			0.0f, 1.0f,  0.0f,		 0.0f, 1.0f, // upper left corner	
	 0.5f,   0.5f, 0.0f,			0.0f, 0.0f,  1.0f,		 1.0f, 1.0f, // upper right corner
	 0.5f,  -0.5f, 0.0f,			1.0f, 1.0f,  1.0f,		 1.0f, 0.0f // lower left corner
};

// index buffer
GLuint indices[] =
{
	0, 2, 1,	// upper left triangle
	0, 3, 2,	// lower right triangle
};

int main()
{
	//init glfw
	glfwInit();

	// tell glfw what version of opengl we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// using core profile (modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a glfw window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Opengl_Victor", NULL, NULL);
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

	// specify the viewport of opengl in the window
	// goes from x = 0 -> 800 and y = 0 -> 800
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind to prevent modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	float scale = 0.5;

	//texture
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


		for (int i = 0; i < 10; ++i) {
			std::cout << "Pixel " << i << ": ";
			for (int c = 0; c < numColCh; ++c) {
				std::cout << static_cast<int>(bytes[i * numColCh + c]) << " ";
			}
			std::cout << std::endl;
		}

	}

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	// main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, scale);
		glBindTexture(GL_TEXTURE_2D, texture);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glDeleteTextures(1, &texture);

	glfwDestroyWindow(window);
	glfwTerminate();

	std::cin.get();
	return 0;
}