workspace "Aesir"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}"

project "AESIR"
	location "AESIR"
	kind "StaticLib" -- Static lib
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h", -- ** search child folders
		"%{prj.name}/src/**.cpp", -- include .shaders?
		"%{prj.name}/src/**.c" -- for glad.c 
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/include",
		"%{prj.name}/src/Renderer/Header Files"
	}

	libdirs
	{
		"%{prj.name}/vendor/lib"
	}

	links
	{
		"glfw3",
        "opengl32"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"--"10.0.22000.0"

		defines
		{
		"AE_PLATFORM_WINDOWS",
		"AE_BUILD_DLL"
		}

		--postbuildcommands
		--{
		--	{"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
		--}

	filter "configurations:Debug"
		defines "AE_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "AE_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "AE_DIST"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" -- executable
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h", -- ** search child folders
		"%{prj.name}/src/**.cpp"
		--"Aesir/src/Renderer/glad.c"
	}

	includedirs
	{
		"AESIR/vendor/spdlog/include",
		"AESIR/vendor/include",
		"AESIR/vendor/lib",
		--"AESIR/src/Renderer/Header Files",
		"AESIR/src"
	}


	links
	{
		"Aesir"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22000.0"

		defines
		{
		"AE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AE_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "AE_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "AE_DIST"
		symbols "on"
