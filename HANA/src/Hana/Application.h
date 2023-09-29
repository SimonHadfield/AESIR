#pragma once

#include "Core.h"

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
