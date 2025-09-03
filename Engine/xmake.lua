--set_runtimes("MTd")

includes("Core")
includes("Function")

target("Engine")
    set_kind("static")
	
    add_files("*.cpp")

    add_deps("Core")
    add_deps("Function")