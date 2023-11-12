#pragma once

#include "Core.h"
#include "utility"
#include "Renderer/Renderer.h"
#include "Application.h"


namespace Hana {

	class HANA_API Input
	{
	public:
		// Keys / Buttons
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);

		// Mouse position
		static std::pair<double, double> GetMousePos();
		static double GetMousePosX();
		static double GetMousePosY();

		static void SetWindow(GLFWwindow* window) { m_Window = window; };

	private:

		static GLFWwindow* m_Window;
	};


};