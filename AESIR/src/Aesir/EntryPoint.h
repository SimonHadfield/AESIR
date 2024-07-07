#pragma once


#ifdef AE_PLATFORM_WINDOWS

extern Aesir::Application* Aesir::CreateApplication();

int main(int argc, char** argv)
{
	Aesir::Log::Init();

	printf("Aesir Engine\n");

	auto app = Aesir::CreateApplication();
	app->Run();
	delete app;
}

#endif