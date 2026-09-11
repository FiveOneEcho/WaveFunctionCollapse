workspace "WaveFunctionCollapse"
    architecture "x64"
    startproject "WFC"
    location "PREMAKE"

    configurations { "Debug", "Release" }

    platforms { "x64" }
    defaultplatform "x64"

    filter "platforms:x64"
        architecture "x64"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        optimize "Off"
        runtime "Debug"

    filter "configurations:Release"
        defines { "NDEBUG" }
        symbols "Off"
        optimize "Full"
        runtime "Release"
    
    filter {}

group "Dependencies"
    include "vendor/glfw"
group ""

project "WFC"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{prj.name}-%{cfg.buildcfg}"

    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp",
        "vendor/imgui/*.cpp",
        "vendor/imgui/backends/*glfw.cpp",
        "vendor/glad/src/glad.c"
    }

    includedirs {
        "src",
        "vendor/glad/include",
        "vendor/glfw/include",
        "vendor/glm",
        "vendor/imgui",
        "vendor/stb"
    }

    links {
        "GLFW"
    }

    filter "system:windows"
        systemversion "latest"
        links { "opengl32" }

    filter {}