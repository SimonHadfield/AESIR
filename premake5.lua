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

IncludeDir = {}
IncludeDir["GLFW"] = "Aesir/vendor/GLFW/include"
IncludeDir["Glad"] = "Aesir/vendor/Glad/include"
IncludeDir["ImGui"] = "Aesir/vendor/imgui"
IncludeDir["glm"] = "Aesir/vendor/glm"
IncludeDir["stb_image"] = "Aesir/vendor/stb_image"

-- include directories
include "AESIR/vendor/imgui/premake5.lua"
include "AESIR/vendor/Glad/premake5.lua"
include "AESIR/vendor/GLFW/premake5.lua"

group "Dependencies"
	include "AESIR/vendor/GLFW"
	include "AESIR/vendor/Glad"
	include "AESIR/vendor/imgui"

group ""

project "AESIR"
	location "AESIR"
	kind "StaticLib" -- Static lib
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h", -- ** search child folders
		"%{prj.name}/src/**.cpp", -- include .shaders?
		"%{prj.name}/src/**.c", -- for glad.c 

		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/include",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/Glad",
		"%{prj.name}/vendor/GLFW",
		"%{prj.name}/vendor",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/Glad/include" -- CHANGE

	}

	links
	{
		"GLFW",
		"ImGui",
		"Glad",
        "opengl32.lib"
	}

	filter "system:windows"
		systemversion "10.0.22000.0"-- "latest"

		defines
		{
		"AE_PLATFORM_WINDOWS",
		"AE_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "AE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AE_DIST"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp" -- executable
	language "C++"
	cppdialect "C++17"
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
		"AESIR/vendor/Glad/include",
		"AESIR/vendor/GLFW/include",
		"AESIR/src",
		"AESIR/vendor"
	}


	links
	{
		"AESIR"
		
	}

	filter "system:windows"
		systemversion "10.0.22000.0"

		defines
		{
			"AE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AE_DIST"
		runtime "Release"
		optimize "on"
