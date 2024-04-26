#include "ImguiLayer.h"

namespace Hana {

	void ImGuiLayer::OnAttach() {

		GLFWwindow* window = Renderer::GetWindowPtr();
		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO();
		//(void)io;
		//
		//ImGui_ImplGlfw_InitForOpenGL(window, true);
		//ImGui_ImplOpenGL3_Init("#version 330");
		//ImGui::StyleColorsDark();
	}

	void ImGuiLayer::OnDetach() {};
	void ImGuiLayer::OnImGuiRender() {};
	void ImGuiLayer::Start() {};
	void ImGuiLayer::End() {};
}
/*
*/