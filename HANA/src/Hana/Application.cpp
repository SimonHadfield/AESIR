#include "Application.h"

#include "Hana/Events/ApplicationEvent.h"
#include "Hana/Log.h"

// to remove after abstraction
#include "Renderer/shaderClass.h"
#include "Renderer/VAO.h"
#include "Renderer/VBO.h"
#include "Renderer/EBO.h"
#include "Renderer/Texture.h"
#include <stb/stb_image.h>
#include <iostream>

// glm
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace Hana {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}

	


	void Application::Run()
	{
		Window window;
		GLFWwindow* m_Window = static_cast<GLFWwindow*> (window.InitWindow());

		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HA_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HA_TRACE(e);
		}

		// ABSTRACTION THIS

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



		//GLfloat vertices[sizeof(Cube_vertices) / sizeof(Cube_vertices[0])];

		/*for (unsigned int i = 0; i < sizeof(Cube_vertices)/sizeof(Cube_vertices[0]); i++)
		{
			vertices[i] = Cube_vertices[i];
		}
		*/

		// set up camera
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		bool firstMouse = true;
		float yaw = -50.0f;
		float pitch = 0.0f;
		float lastX = 800.0f / 2.0;
		float lastY = 600.0 / 2.0;
		float fov = 45.0f;

		// delta time
		GLfloat deltaTime = 0.0f;
		GLfloat currentTime = 0.0f;
		GLfloat prevTime = 0.0f;

		//		-- SHADERS

		// Cube
		HA_WARN("ABSTRACT RENDERING FROM APPLICATION.CPP");
		HA_WARN("CHANGE SHADER TO RELATIVE PATH");
		Shader shaderProgram("A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.vert", "A:/dev/Hana/HANA/HANA/src/Renderer/res/shaders/default.frag"); // create shader with vertexShader and fragmentShader
		//Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag"); // create shader with vertexShader and fragmentShader
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
		HA_WARN("CHANGE TEXTURE TO RELATIVE PATH");
		Texture tex0("A:/dev/Hana/HANA/HANA/src/Renderer/res/textures/Logo.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
		tex0.Bind();
		tex0.texUnit(shaderProgram, "tex0", 0);


		// grid 

		GLfloat grid_vertices[] =
		{
			//   x     y	 z

			//	LEFT-RIGHT
				-5.0f, 0.0f, -2.0f,
				 5.0f, 0.0f, -2.0f,

				-5.0f, 0.0f, -1.6f,
				 5.0f, 0.0f, -1.6f,

				-5.0f, 0.0f, -1.2f,
				 5.0f, 0.0f, -1.2f,

				-5.0f, 0.0f, -0.8f,
				 5.0f, 0.0f, -0.8f,

				-5.0f, 0.0f, -0.4f,
				 5.0f, 0.0f, -0.4f,

				-5.0f, 0.0f, 0.0f,
				 5.0f, 0.0f, 0.0f,

				-5.0f, 0.0f, 0.4f,
				 5.0f, 0.0f, 0.4f,

				-5.0f, 0.0f, 0.8f,
				 5.0f, 0.0f, 0.8f,

				-5.0f, 0.0f, 1.2f,
				 5.0f, 0.0f, 1.2f,

				-5.0f, 0.0f, 1.6f,
				 5.0f, 0.0f, 1.6f,

				-5.0f, 0.0f, 2.0f,
				 5.0f, 0.0f, 2.0f,

				 //	FRONT-BACK
					 -2.0f, 0.0f,  5.0f,
					 -2.0f, 0.0f, -5.0f,

					 -1.6f, 0.0f,  5.0f,
					 -1.6f, 0.0f, -5.0f,

					 -1.2f, 0.0f,  5.0f,
					 -1.2f, 0.0f, -5.0f,

					 -0.8f, 0.0f, -5.0f,
					 -0.8f, 0.0f,  5.0f,

					 -0.4f, 0.0f, -5.0f,
					 -0.4f, 0.0f,  5.0f,

					  0.0f, 0.0f, -5.0f,
					  0.0f, 0.0f,  5.0f,

					  0.4f, 0.0f, -5.0f,
					  0.4f, 0.0f,  5.0f,

					  0.8f, 0.0f, -5.0f,
					  0.8f, 0.0f,  5.0f,

					  1.2f, 0.0f, -5.0f,
					  1.2f, 0.0f,  5.0f,

					  1.6f, 0.0f, -5.0f,
					  1.6f, 0.0f,  5.0f,

					  2.0f, 0.0f, -5.0f,
					  2.0f, 0.0f,  5.0f,
		};

		GLint grid_indices[] =
		{
			0, 1
		};

		//		-- SHADERS
		VAO VAO2;										// create vertex array
		VAO2.Bind();									// bind vertexy array

		VBO VBO2(grid_vertices, sizeof(grid_vertices));			// create vertex buffer
		//EBO EBO2(indices, sizeof(indices));			// indices not currently needed

		//	link VBO to VAO
		//	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
		VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);					// link position vertices

		// Unbind to prevent modifying
		VAO2.Unbind();
		VBO2.Unbind();
		//EBO1.Unbind();								// indices not currently needed


		while (!glfwWindowShouldClose(m_Window))
		{
			// Abstract below
			// processInput(m_Window);
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

			HA_WARN("window width, window height, fov given explicitly");

			projection = glm::perspective(glm::radians(fov), 1280.0f / 720.0f, 0.1f, 100.0f);		// set projection to perspective 

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

			tex0.Unbind();
			VAO1.Unbind();


			// grid
			model = glm::mat4(1.0f);	// grid is in world view
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			VAO2.Bind();

			glDrawArrays(GL_LINES, 0, 44);

			VAO2.Unbind();
			// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(m_Window); // show new rendered frame
			glfwPollEvents();

			prevTime = currentTime;
		}

		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}