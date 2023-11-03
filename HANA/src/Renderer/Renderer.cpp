#include "Renderer/Renderer.h"

namespace Hana {
	
	Renderer::Renderer() {
	// Init GLFW/GLAD global settings
	};

	Renderer::~Renderer() {
		glfwTerminate();
	};

	void Renderer::StartFrame() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	};

	// void Renderer::InsertRenderable() {};
	
	void Renderer::EndFrame() {
		// glfwSwapBuffers(window);
		glfwPollEvents();
	};
}