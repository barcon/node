-- premake5.lua
workspace "nodes"
	configurations { "Debug", "Release" }
	location "build"

project "nodes"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir "build/%{cfg.buildcfg}"
	includedirs { "../utils/src" }	
	includedirs { "../logger/src" }	
	includedirs { "../eilig/src" }	

	files { "src/**.hpp", "src/**.cpp" }

	filter "configurations:Debug"
		architecture "x86_64"     
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		architecture "x86_64"     
		defines { "NDEBUG" }
		optimize "Speed"