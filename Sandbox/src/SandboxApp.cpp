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
