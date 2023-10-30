#include "Window.h"

namespace Hana {

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
            HA_CRITICAL("Failed to create GLFW window");
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(m_Window);					// introduce window into current context
        gladLoadGL();									// load glad
        
        //		-- GLOBAL SETTINGS
        glEnable(GL_DEPTH_TEST);						// Depth test for rendering order
        //glEnable(GL_CULL_FACE);
        glViewport(0, 0, window_width, window_height);	// specify the viewport in given window

        return static_cast<void*>(m_Window);
    }

    void RenderContext()
    {
        
        

        ////		-- SHADERS

        //// Cube
        //Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag"); // create shader with vertexShader and fragmentShader
        //VAO VAO1;										// create vertex array
        //VAO1.Bind();									// bind vertexy array

        //VBO VBO1(vertices, sizeof(vertices));			// create vertex buffer

        ////EBO EBO1(indices, sizeof(indices));			// indices not currently needed

        ////	link VBO to VAO
        ////	1 VBO, 2 GLuint layout, 3 GLuint numComponents, 4 GLenum type, 5 GLsizeiptr stride, 6 void* offset
        //VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);							// link position vertices
        //VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));	// link texture vertices

        //// Unbind to prevent modifying
        //VAO1.Unbind();
        //VBO1.Unbind();
        ////EBO1.Unbind();								// indices not currently needed

        //// texture (create texture, bind and assign to uniform)
        //Texture tex0("res/textures/Logo.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
        //tex0.Bind();
        //tex0.texUnit(shaderProgram, "tex0", 0);

    }
}