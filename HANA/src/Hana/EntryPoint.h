#pragma once

#ifdef HA_PLATFORM_WINDOWS

extern Hana::Application* Hana::CreateApplication();

int main(int argc, char** argv)
{
	Hana::Log::Init();
	HA_CORE_WARN("Initialized Log");
	HA_INFO("Hello");

	printf("Hana Engine\n");
	auto app = Hana::CreateApplication();
	app->Run();
	delete app;
}

#endif