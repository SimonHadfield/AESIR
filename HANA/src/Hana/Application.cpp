#include "Application.h"

#include "Hana/Events/ApplicationEvent.h"
#include "Hana/Log.h"



namespace Hana {
	Application::Application()
	{
	}
	Application::~Application()
	{
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

		Window window;
		GLFWwindow* m_Window = static_cast<GLFWwindow*> (window.InitWindow());
		window.RenderContext(m_Window);

	}


}