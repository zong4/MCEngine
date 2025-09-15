target("Editor")
    set_kind("binary")

    if is_plat("windows") then
        add_ldflags("/subsystem:console")
    end

    add_deps("Core")
    add_deps("Function")
    add_deps("Engine")
    
    add_files("src/*.cpp")
