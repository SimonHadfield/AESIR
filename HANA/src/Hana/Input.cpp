#include "Input.h"


namespace Hana {

	GLFWwindow* Input::m_Window = nullptr;


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

	//std::pair<double, double> Input::GetMousePos() {
	//	GLFWwindow* window = Hana::Application::GetWindow();
	//	double xpos, ypos;
	//	auto MousePos = glfwGetCursorPos(window, xpos, ypos);
	//	return { xpos, ypos };
	//}
	//
	//float Input::GetMousePosX()
	//{
	//	std::pair<double, double> MousePos = GetMousePos();
	//	return (float)MousePos.first;
	//}
	//
	//float Input::GetMousePosY()
	//{
	//	std::pair<double, double> MousePos = GetMousePos();
	//	return (float)MousePos.second;
	//}

}