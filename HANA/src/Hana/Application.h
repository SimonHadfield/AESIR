#pragma once

#include "Core.h"
#include "Events/Event.h"

// init window and renderer
#include "Window.h"

namespace Hana {

	class HANA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// to define in client
	Application* CreateApplication();

}
