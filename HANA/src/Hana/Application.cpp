#include "Application.h"

#include "Hana/Events/ApplicationEvent.h"
#include "Hana/Log.h"

namespace Hana {
	
	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer) 
	{
		m_LayerStack.PushLayer(layer);
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

		while (!RenderContext.ShouldClose())
		{
			RenderContext.StartFrame();

			for (Layer* layer : m_LayerStack) {
						layer->OnRender();
						layer->OnUpdate();
			}
		
			RenderContext.EndFrame();
		}


	}


}