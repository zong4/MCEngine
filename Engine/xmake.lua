includes("Core")
includes("Function")

target("Engine")
    set_kind("shared")

    add_deps("Core")
    add_deps("Function")