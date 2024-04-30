#pragma once

#include <GLFW/glfw3.h>
#include "Core.h"

namespace Aesir {

	class AESIR_API Time
	{
	public:
		static double GetTime() { return glfwGetTime(); }
	};

}