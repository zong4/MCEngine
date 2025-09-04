target("Function")
    set_kind("static")

    add_deps("Core")
    
    add_headerfiles("src/**/*.hpp")
    add_files("src/**/*.cpp")
    add_includedirs("src", {public = true})
