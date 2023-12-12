#include "Hana.h" 
#include "Hana/EntryPoint.h"

//#include "Pong/GameLayer.h"
#include "TrumpJump/GameLayer.h"
#include "3DTestScene/SceneLayer.h"

class Sandbox : public Hana::Application
{
public:

	Sandbox()
	{


		PushLayer(new GameLayer());
		//PushLayer(new SceneLayer());

	}

	~Sandbox()
	{
	}
};



Hana::Application* Hana::CreateApplication()
{
	return new Sandbox();
}
