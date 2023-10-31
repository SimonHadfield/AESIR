#pragma once

// include glad and glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Render classes
#include "Renderer/shaderClass.h"
#include "Renderer/VAO.h"
#include "Renderer/VBO.h"
#include "Renderer/EBO.h"
#include "Renderer/Texture.h"
#include <stb/stb_image.h>

// include renderer
//#include "Renderer/Renderer.h"
//#include "Renderer/HanaCube.h"
//#include "Renderer/HanaGrid.h"

// logger
#include "Log.h"

namespace Hana {
	class Window
	{
	public:
		Window();
		~Window();
		virtual void* InitWindow();
		void RenderContext(GLFWwindow* m_Window);
		void Shutdown();
	private:
		GLFWwindow* m_Window;
	};
}
