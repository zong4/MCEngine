-- Graphics
add_requires("glfw", "glad")

target("Core")
    set_kind("static")
    
    add_headerfiles("src/**/*.hpp")
    add_files("src/**/*.cpp")
    add_includedirs("src", {public = true})

    add_files("vendor/Remotery/lib/Remotery.c")
    add_includedirs("vendor/Remotery", {public = true})

    -- Graphics
    add_packages("glfw", "glad")
