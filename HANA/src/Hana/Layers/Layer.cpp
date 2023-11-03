#include "Layer.h"

namespace Hana {
	Layer::Layer(const std::string& name) : name(name) {};

	Layer::~Layer() {};

	void Layer::OnAttach() {};
	void Layer::OnDetach() {};
	// void Layer::OnUpdate() {};
	void Layer::OnRender() {};

	const std::string& Layer::GetName() const { return name; };
}