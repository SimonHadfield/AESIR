#pragma once


#include "Renderer/Renderer.h"

//#include "../Core.h"
#include "Layer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


namespace Aesir {
	class AESIR_API ImGuiLayer : public Layer
	{
	public:

		//~ImGuiLayer();

		//void Init();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		//virtual void OnUpdate() override;
		//virtual void OnImGuiRender() override;
		//virtual void OnUpdate() = 0;

		void Start();
		void End();

	};
}