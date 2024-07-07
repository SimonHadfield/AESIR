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

include "AESIR/vendor/imgui/premake5.lua"
include "AESIR/vendor/include/Glad/premake5.lua"

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
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/include/Glad/include"
	}

	print("%{prj.name}")

	libdirs
	{
		"%{prj.name}/vendor/lib",

	}

	links
	{
		"ImGui",
		"Glad",
        "opengl32.lib"
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
	}

	includedirs
	{
		"AESIR/vendor/spdlog/include",
		"AESIR/vendor/include",
		"AESIR/vendor/lib",
		"AESIR/vendor/imgui",
		"AESIR/src",
		"AESIR/vendor/include/Glad/include"
	}


	links
	{
		"AESIR",
		"ImGui",
		"Glad",
        "opengl32.lib"
		
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
