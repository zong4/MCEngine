target("Function")
    set_kind("static")
    
    add_headerfiles("src/**/*.hpp")
    add_files("src/**/*.cpp")
    add_includedirs("src", {public = true})

    add_deps("Core")
