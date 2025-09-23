-- VS Code
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

add_rules("mode.debug", "mode.release")

set_languages("c++20")

add_cflags("-Werror")
add_cxxflags("-Werror")

includes("Engine")
includes("Editor")