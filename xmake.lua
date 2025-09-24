-- VS Code
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

-- Language
set_languages("c++20")

add_cflags("-Werror")
add_cxxflags("-Werror")

-- Defines
add_rules("mode.debug", "mode.release")
if is_mode("debug") then
    add_defines("DEBUG")
end

add_defines("PROJECT_ROOT=\"$(projectdir)\"")

includes("Engine")
includes("Editor")