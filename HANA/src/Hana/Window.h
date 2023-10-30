#pragma once

// include glad and glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// include renderer
// #include "Renderer/Renderer.h"

// logger
#include "Log.h"

namespace Hana {
	class Window
	{
	public:
		Window();
		~Window();
		virtual void* InitWindow();
		void RenderContext();
		void Shutdown();
	private:
		GLFWwindow* m_Window;
	};
}
