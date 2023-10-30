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
		Window window;
		void* m_Window = window.InitWindow();

		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HA_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HA_TRACE(e);
		}

		bool i = true;
		while (i) 
		{
		};
	}
}