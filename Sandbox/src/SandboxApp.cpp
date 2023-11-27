#include "Hana.h" 
#include "Hana/EntryPoint.h"

#include "Pong/GameLayer.h"

class Sandbox : public Hana::Application
{
public:

	Sandbox()
	{


		PushLayer(new GameLayer());


	}

	~Sandbox()
	{
	}
};



Hana::Application* Hana::CreateApplication()
{
	return new Sandbox();
}
