#pragma once

#include <vector>
#include <Hana/Layers/Layer.h>
#include "Hana/Layers/ImguiLayer.h"

namespace Hana {
	class LayerStack
	{
	public:

		virtual ~LayerStack();

		virtual void PushLayer(Layer* layer);
		virtual void PopLayer(Layer* layer);

		//virtual void PushOverlay(Layer* overlay);
		//virtual void PopOverlay(Layer* overlay);
		//virtual void Render();

		const std::vector<Layer*>& GetLayers() const { return m_Layers; }

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}
