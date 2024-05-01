#include "Window.h"
#include "Renderer/HanaCube.h"


namespace Aesir {

    Window::Window() {}
    Window::~Window() {}

    void* Window::InitWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// assign opengl version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					// assign "
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// using core profile

        // window size
        const unsigned int window_width = 1280;
        const unsigned int window_height = 720;

        // Initialize GLFW and create a window.
        if (glfwInit()) {
            m_Window = glfwCreateWindow(window_width, window_height, "My Window", nullptr, nullptr);
        }
        
        if (m_Window == NULL)																			// Check GLFW window opens
        {
            AE_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(m_Window);					// introduce window into current context
        gladLoadGL();									    // load glad
        
        //		-- GLOBAL SETTINGS
        glEnable(GL_DEPTH_TEST);						    // Depth test for rendering order
        //glEnable(GL_CULL_FACE);
        glViewport(0, 0, window_width, window_height);	    // specify the viewport in given window

        return static_cast<void*>(m_Window);
    }


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

	// Callback declarations
	void framebuffer_size_callback(GLFWwindow* m_Window, int width, int height);
	void mouse_callback(GLFWwindow* m_Window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* m_Window, double xoffset, double yoffset);
	void processInput(GLFWwindow* m_Window);

	void Window::RenderInit()
	{
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);						// callback for resizing window
		glfwSetCursorPosCallback(m_Window, mouse_callback);											// callback - mouseInputs
		glfwSetScrollCallback(m_Window, scroll_callback);											// callback - scrollInput
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);								// capture mouse
	}


    void Window::RenderContext(GLFWwindow* m_Window)
    {
		/*
		//Renderable::DrawQuad2D(0.0f, 0.0f, 10.0f, 10.0f);

		GLfloat vertices[sizeof(Cube_vertices) / sizeof(Cube_vertices[0])];
		if (sizeof(Cube_vertices) > 0)
		{
			for (unsigned int i = 0; i < sizeof(Cube_vertices) / sizeof(Cube_vertices[0]); i++)
			{
				vertices[i] = Cube_vertices[i];
			}
		}

		//		-- SAEDERS

		// Cube
		AE_WARN("CAENGE SAEDER TO RELATIVE PATH");
		Shader shaderProgram("A:/dev/Aesir/AESIR/AESIR/src/Renderer/res/shaders/texture.vert", "A:/dev/Aesir/AESIR/AESIR/src/Renderer/res/shaders/texture.frag"); // create shader with vertexShader and fragmentShader
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
		AE_WARN("CAENGE TEXTURE TO RELATIVE PATH");
		Texture tex0("A:/dev/Aesir/AESIR/AESIR/src/Renderer/res/textures/Logo.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
		tex0.Bind();
		tex0.texUnit(shaderProgram, "tex0", 0);

		// generated grid    
		unsigned int lines = 11;
		float length_lines = 10.0f;
		GLfloat grid_vertices[240 * sizeof(GLfloat)]; // 2 (F-B L-R) *	lines * 2 (start, end) * 3 (x, y, z) * sizeof(type)

		float stepsize;
		int steps;

		for (int i = 0; i < (lines*2*3*2); i += 6)
		{
			stepsize = length_lines / lines;
			steps = i / 6;
			if (i < lines * 2 * 3)
			{
				// LEFT-RIGHT LINES
				grid_vertices[i] =     -length_lines / 2;	grid_vertices[i + 1] = 0.0f;	grid_vertices[i + 2] =  (stepsize * steps) - (stepsize * (lines - 1) ) / 2;	// start x,y,z
				grid_vertices[i + 3] =  length_lines / 2;	grid_vertices[i + 4] = 0.0f;	grid_vertices[i + 5] =  (stepsize * steps) - (stepsize * (lines - 1) ) / 2;	// end x,y,z
			}
			else {
				// FRONT-BACK LINES
				// - length_lines -> offset for 2nd set of vertices
				grid_vertices[i] =		(stepsize * steps) - (stepsize * (lines - 1)) / 2 - length_lines;	grid_vertices[i + 1] = 0.0f;	grid_vertices[i + 2] = -length_lines / 2;  // start x,y,z
				grid_vertices[i + 3] =	(stepsize * steps) - (stepsize * (lines - 1)) / 2 - length_lines;	grid_vertices[i + 4] = 0.0f;	grid_vertices[i + 5] =  length_lines / 2;  // end x,y,z
			}
		}

		GLint grid_indices[] =
		{
			0, 1
		};
		
		//		-- SAEDERS
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
			processInput(m_Window);
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
			projection = glm::perspective(glm::radians(fov), 1280.0f / 720.0f, 0.1f, 100.0f);								// set projection to perspective 

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
		*/
    }

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}


	// CALLBACKS

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height); // match viewport to current window size
	}

	void processInput(GLFWwindow* m_Window)
	{
		if ((glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) && (GLFW_CURSOR_DISABLED))
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly


		if (glfwGetKey(m_Window, GLFW_KEY_W) || glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS)				// move camera forward -	W / ARROW-UP
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(m_Window, GLFW_KEY_S) || glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)				// move camera backwards -	S / ARROW-DOWN
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(m_Window, GLFW_KEY_A) || glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS)				// move camera left -		A / ARROW-LEFT
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(m_Window, GLFW_KEY_D) || glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS)				// move camera right -		D / ARROW-RIGHT
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(m_Window, GLFW_KEY_E) || glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)				// move camera up -			E / SPACEBAR
			cameraPos += cameraUp * cameraSpeed;
		if (glfwGetKey(m_Window, GLFW_KEY_Q) || glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)		// move camera down -		Q / LEFT-CTRL
			cameraPos -= cameraUp * cameraSpeed;

	}

	// mouse movement callback
	void mouse_callback(GLFWwindow* m_Window, double xposIn, double yposIn)
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
	void scroll_callback(GLFWwindow* m_Window, double xoffset, double yoffset)
	{
		fov -= (float)yoffset;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 45.0f)
			fov = 45.0f;
	}

}