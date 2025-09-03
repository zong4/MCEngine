target("Editor")
    set_kind("binary")

    add_deps("Engine")
    
    add_files("src/*.cpp")
