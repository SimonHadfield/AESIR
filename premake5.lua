workspace "Hana"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}"

project "Hana"
	location "Hana"
	kind "SharedLib" -- dynamic lib
	language "C++"

	targetdir ("bin/" .. outputdir .. "/{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/{prj.name}")

	files
	{
		"%{prj.name}/src/**.h", -- ** search child folders
		"%{prj.name}/src/**.cpp", -- include .shaders?
		"%{prj.name}/src/**.c" -- for glad.c 
	}

	includedirs
	{
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
		"glfw3.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22000.0"

		defines
		{
		"HA_PLATFORM_WINDOWS",
		"HA_BUILD_DLL"
		}

		postbuildcommands
		{
			{"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"}
		}

	filter "configurations:Debug"
		defines "HA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HA_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" -- executable
	language "C++"

	targetdir ("bin/" .. outputdir .. "/{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/{prj.name}")

	files
	{
		"%{prj.name}/src/**.h", -- ** search child folders
		"%{prj.name}/src/**.cpp"
		--"Hana/src/Renderer/glad.c"
	}

	includedirs
	{
		"Hana/vendor/spdlog/include",
		"Hana/vendor/include",
		"Hana/vendor/lib",
		"Hana/src/Renderer/Header Files",
		"Hana/src"
	}

	links
	{
		"Hana"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.22000.0"

		defines
		{
		"HA_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HA_DIST"
		symbols "On"
