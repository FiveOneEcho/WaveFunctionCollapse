project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "On"

    targetdir ("../../bin/%{cfg.buildcfg}")
    objdir ("../../bin-int/%{prj.name}-%{cfg.buildcfg}")

    -- Need to glob in macOS Objective-C m files later if building for mac
    files {
        "include/GLFW/*.h",
        "src/*.c",
        "src/*.h"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS" }
        removefiles {
            "src/cocoa_*",
            "src/nsgl_*",
            "src/x11_*",
            "src/glx_*",
            "src/wl_*",
            "src/linux_*",
            "src/macos_*",
            "src/posix_*"
        }

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"
        runtime "Debug"

    filter "configurations:Release"
        symbols "Off"
        optimize "Full"
        runtime "Release"

    filter {}