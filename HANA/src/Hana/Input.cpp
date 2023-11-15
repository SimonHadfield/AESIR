#include "Input.h"


namespace Hana {

	bool Input::IsKeyPressed(int keycode) {

		GLFWwindow* window = Renderer::GetWindowPtr();
		
		if (window != nullptr) {
			auto keyState = glfwGetKey(window, keycode);	
			return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
		}
		return false;
	}

	bool Input::IsMouseButtonPressed(int button) {
	
		GLFWwindow* window = Renderer::GetWindowPtr();
		
		if (window != nullptr) {
			auto buttonState = glfwGetMouseButton(window, button);
			return buttonState == GLFW_PRESS;
		}
		return false;
	}

	std::pair<double, double> Input::GetMousePos() {
		GLFWwindow* window = Renderer::GetWindowPtr();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { xpos, ypos };
	}
	
	double Input::GetMousePosX()
	{
		std::pair<double, double> MousePos = GetMousePos();
		return MousePos.first;
	}
	
	double Input::GetMousePosY()
	{
		std::pair<double, double> MousePos = GetMousePos();
		return MousePos.second;
	}

}