#pragma once

// include glad and glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// include window
#include "Aesir/Log.h"


// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// STB
#include <stb/stb_image.h>

// Render classes
//#include "Renderer/shaderClass.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/VAO.h"
#include "Renderer/VBO.h"
#include "Renderer/EBO.h"
#include "Renderer/Renderable.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


class Renderable;

namespace Aesir {

	class Renderer
	{
	public:

		void* Init();
		//void ImGuiInit();
		void StartFrame();
		bool ShouldClose();

		void EndFrame();
		void Shutdown();
		
		static GLFWwindow* GetWindowPtr() { return m_Window; };

	private:
		static inline GLFWwindow* m_Window;

	};

}
