#pragma once

#include <GLFW/glfw3.h>
#include "Core.h"

namespace Hana {

	class HANA_API Time
	{
	public:
		static double GetTime() { return glfwGetTime(); }
	};

}