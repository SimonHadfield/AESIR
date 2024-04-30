#pragma once

// include renderer
#include "Renderer/Renderer.h"
#include "Renderer/Renderable.h"

// logger
#include "Log.h"

namespace Aesir {
	class Window
	{
	public:
		Window();
		~Window();
		virtual void* InitWindow();
		void RenderInit();
		void RenderContext(GLFWwindow* m_Window);
		void ImGuiInit();
		void Shutdown();
	private:
		GLFWwindow* m_Window;
	};
}
