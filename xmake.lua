add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

add_rules("mode.debug", "mode.release")

includes("Engine")
includes("Editor")