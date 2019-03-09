-- Written by William J Hughes.

project_name = "wolfenstein-sfml"


workspace "%{project_name}"
  architecture "x64"
 -- Build Configurations...
    configurations { "Development", "RC" }

output_dir = "%{cfg.system}_%{cfg.buildcfg}-%{cfg.architecture}"

vendor = {}
vendor["sfml"] = "deps/SFML-2.5.1/include"

project "wolfenstein-sfml"
  
    kind "ConsoleApp"
      language "C++"
  
  targetdir("bin/" .. output_dir .. "/")
     objdir("bin/" .. output_dir .. "/data/obj/")

  files { "SFFML/src/**.hpp", "SFML/src/**.cpp" }
    includedirs { "%{vendor.sfml}" }

  libdirs { "deps/SFML-2.5.1/lib" }
    links { "opengl32.lib", "vorbis.lib","ogg.lib","winmm.lib","gdi32.lib","advapi32.lib","user32.lib" }

  filter "system:windows"
    cppdialect "C++17"
      systemversion "latest"

    defines { "GAME_PLATFORM_WINDOWS", "SFML_STATIC" }

  filter "configurations:Development"
    defines "GAME_DEBUG"
      runtime "Debug"
    symbols "On"

    links { "sfml-audio-s-d.lib", "sfml-graphics-s-d.lib", "sfml-network-s-d.lib", "sfml-system-s-d.lib", "sfml-window-s-d.lib" }

  filter "configurations:RC"
    defines "GAME_PUBLIC"
      runtime "Release"
    optimize "On"

    links { "sfml-audio-s.lib", "sfml-graphics-s.lib", "sfml-network-s.lib", "sfml-system-s.lib", "sfml-window-s.lib" }