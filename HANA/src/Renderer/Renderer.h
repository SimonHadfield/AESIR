#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// default rendering vertices
#include "Renderer/HanaCube.h"

namespace Hana {

	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();

		virtual void StartFrame();
		virtual void EndFrame();

		// virtual void RenderLayerStack(LayerStack& layerstack);
		// virtual void InsertRenderable(const Renderable* renderable);
	};

}
