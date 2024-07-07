#pragma once

#include "Core.h"
#include "Events/Event.h"

// init window and renderer
#include "Window.h"
#include "Layers/LayerStack.h"
#include "Renderer/Renderer.h"

#include "Time.h"

namespace Aesir {

	class AESIR_API Application
	{
	public:
		// Application();
		virtual ~Application();
		
		void Run();
		
		virtual void PushLayer(Layer* layer);

	private:
		LayerStack m_LayerStack;
		bool m_Running = true;

		Renderer RenderContext;
	};

	// to define in client
	Application* CreateApplication();

}
