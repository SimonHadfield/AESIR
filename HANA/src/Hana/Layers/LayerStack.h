#pragma once

#include <Hana/Layers/Layer.h>
#include <vector>

namespace Hana {
	class LayerStack
	{
	public:
		LayerStack();
		virtual ~LayerStack();

		virtual void PushLayer(Layer* layer);
		virtual void PopLayer(Layer* layer);
		virtual void PushOverlay(Layer* overlay);
		virtual void PopOverlay(Layer* overlay);
		virtual void Render();

		const std::vector<Layer*>& GetLayers();

	private:
		std::vector<Layer*> m_Layers;
		unsigned int layerInsertIndex = 0;
	};
}
