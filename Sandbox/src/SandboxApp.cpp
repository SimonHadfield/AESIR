#include "Hana.h" 

class Sandbox : public Hana::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};


Hana::Application* Hana::CreateApplication()
{
	return new Sandbox();
}

// Example usage for renderer, layer, layerstack:
	// Renderer* renderer = Renderer::Create();
	// renderer->Init();
	// LayerStack layerStack;
	// layerStack.PushLayer(new MyCustomLayer("CustomLayer"));
	// ...
