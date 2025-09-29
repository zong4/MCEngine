add_requires("entt")

target("Function")
    set_kind("static")

    add_deps("Core")
    
    add_headerfiles("Sources/**/*.hpp")
    add_files("Sources/**/*.cpp")
    add_includedirs("Sources", {public = true})

    add_packages("entt", {public = true})
