#include "Aesir.h" 
#include "Aesir/EntryPoint.h"

//#include "Pong/GameLayer.h"
#include "TrumpJump/GameLayer.h"
#include "3DTestScene/SceneLayer.h"

class Sandbox : public Aesir::Application
{
public:

	Sandbox()
	{


		//PushLayer(new GameLayer());
		PushLayer(new SceneLayer());

	}

	~Sandbox()
	{
	}
};



Aesir::Application* Aesir::CreateApplication()
{
	return new Sandbox();
}
