-- premake5.lua
workspace "node"
	configurations { "Debug", "Release", "ReleaseCL"  }
	location "build"

project "node"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	architecture "x86_64"
	objdir "%{cfg.location}/obj/%{cfg.platform}_%{cfg.buildcfg}"

	targetdir "build/%{cfg.buildcfg}"
	includedirs { "../utils/src" }	
	includedirs { "../logger/src" }	
	includedirs { "../eilig/src" }	

	files { "src/**.hpp", "src/**.cpp" }

	filter "configurations:Debug" 
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"   
		defines { "NDEBUG" }
		optimize "Speed"

	filter "configurations:ReleaseCL"   
		defines { "NDEBUG", "EILIG_ENABLE_OPENCL" }
		optimize "Speed"	
		
		includedirs { "../club/src" }	
		includedirs { "../opencl/inc" }