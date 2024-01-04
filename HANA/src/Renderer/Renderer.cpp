#include "Renderer/Renderer.h"


namespace Hana {

	//Renderer::~Renderer() {
	//glfwTerminate();
	//};
    void framebuffer_size_callback(GLFWwindow* m_Window, int width, int height);
    // void mouse_callback(GLFWwindow* m_Window, double xpos, double ypos);
    // void scroll_callback(GLFWwindow* m_Window, double xoffset, double yoffset);
    // void processInput(GLFWwindow* m_Window);


	void* Renderer::Init() {
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
        gladLoadGL();									    // load glad

        //		-- GLOBAL SETTINGS
        glEnable(GL_DEPTH_TEST);						    // Depth test for rendering order
        //glEnable(GL_CULL_FACE);
        glViewport(0, 0, window_width, window_height);	    // specify the viewport in given window

        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);						// callback for resizing window

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

		return static_cast<void*>(m_Window);
	};

	void Renderer::ImGuiInit()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
        
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
	}

    bool Renderer::ShouldClose() {
        return glfwWindowShouldClose(m_Window);
    };

	void Renderer::StartFrame() {
		glClearColor(0.01f, 0.0f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

        // test

        

        //renderable->DrawBackground();
	};


	void Renderer::EndFrame() {
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	};

    
	
    void Renderer::Shutdown() { glfwSetWindowShouldClose(m_Window, TRUE); };

    

}