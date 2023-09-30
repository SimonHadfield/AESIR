#pragma once

#ifdef HA_PLATFORM_WINDOWS

extern Hana::Application* Hana::CreateApplication();

int main(int argc, char** argv)
{
	Hana::Log::Init();
	Hana::Log::GetCoreLogger()->warn("Initialized Log");
	Hana::Log::GetClientLogger()->info("Hello");

	printf("Hana Engine\n");
	auto app = Hana::CreateApplication();
	app->Run();
	delete app;
}

#endif