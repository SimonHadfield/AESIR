#include "Application.h"

#include "Aesir/Events/ApplicationEvent.h"
#include "Aesir/Log.h"
#include "Layers/ImguiLayer.h"

namespace Aesir {
	
	Application::~Application() {}

	void Application::PushLayer(Layer* layer) 
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			AE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			AE_TRACE(e);
		}

		
		RenderContext.Init();
		RenderContext.ImGuiInit();

		// load resources
		for (Layer* layer : m_LayerStack) {
			layer->LoadResources();
		}

		while (!RenderContext.ShouldClose())
		{
			RenderContext.StartFrame();

			for (Layer* layer : m_LayerStack) {
						layer->OnRender();
						layer->OnUpdate();
						layer->OnImGuiRender();
						//imguilayer->OnRender();
						//imguilayer->Init();
			}

			RenderContext.EndFrame();
		}


	}


}