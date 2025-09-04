target("Editor")
    set_kind("binary")

    add_deps("Core")
    add_deps("Function")
    add_deps("Engine")
    
    add_files("src/*.cpp")
