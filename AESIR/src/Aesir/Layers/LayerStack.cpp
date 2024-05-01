#include "LayerStack.h"

namespace Aesir {

	
	LayerStack::~LayerStack() {
	for (Layer* layer : m_Layers)
			delete layer;
	};

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.end()) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	// 
	// const std::vector<Layer*>& LayerStack::GetLayers() const { return layers; }
}