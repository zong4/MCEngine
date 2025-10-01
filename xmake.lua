set_project("MinecraftEngine")

set_version("1.0.0")
set_languages("c++20")

-- Warnings
add_cflags("-Werror")
add_cxxflags("-Werror")

-- Mode Defines
add_rules("mode.debug", "mode.release")
if is_mode("debug") then
    add_defines("DEBUG")
end

-- Global Defines
add_defines('PROJECT_ROOT=R"($(projectdir)//)"')

-- VS Code Specific
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

-- Targets
includes("Engine")
includes("Editor")