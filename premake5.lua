workspace "SFML_SKELETON"
    architecture "x64"
    configurations { "Debug", "Release" }
    location "build"

project "SFML_SKELETON"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files { "src/**.cpp", "src/**.h", "src/**.hpp", "dependencies/ImGui/*.*"}

filter "configurations:*"
    defines { "SFML_STATIC" }
    includedirs { "dependencies/SFML/include", "dependencies/ImGui"}
    libdirs { "dependencies/SFML/lib" }
    links
    {
        "opengl32",
        "freetype",
        "winmm",
        "gdi32",
        "flac",
        "vorbisenc",
        "vorbisfile",
        "vorbis",
        "ogg",
        "ws2_32"
    }

filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"
    links
    {	
        "sfml-graphics-s-d",
        "sfml-window-s-d",
        "sfml-system-s-d",
        "sfml-audio-s-d",
        "sfml-network-s-d"
    }

filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    links
    {	
        "sfml-graphics-s",
        "sfml-window-s",
        "sfml-system-s",
        "sfml-audio-s",
        "sfml-network-s"
    }

newaction {
    trigger = "clean",
    description = "Remove build & bin files",
    execute = function()
        os.rmdir("./bin")
        os.rmdir("./build")
    end
}