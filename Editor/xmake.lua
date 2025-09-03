add_deps("Engine")

target("Editor")
    set_kind("binary")
    
    add_files("src/*.cpp")
