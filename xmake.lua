-- VS Code
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

add_rules("mode.debug", "mode.release")

set_languages("c++20")

includes("Engine")
includes("Editor")