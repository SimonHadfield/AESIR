#pragma once

// include glad and glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hana {
	class Window
	{
	public:
		Window();
		~Window();
		virtual void* InitWindow();
		
	private:
		GLFWwindow* m_Window;
	};
}
