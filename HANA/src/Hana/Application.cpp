#include "Application.h"

#include "Hana/Events/ApplicationEvent.h"
#include "Hana/Log.h"
#include "Layers/ImguiLayer.h"

namespace Hana {
	
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
			HA_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HA_TRACE(e);
		}

		RenderContext.Init();
		RenderContext.ImGuiInit();

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