add_requires("imgui v1.92.1-docking", {configs = {glfw_opengl3 = true}})

target("Function")
    set_kind("static")

    add_deps("Core")
    
    add_headerfiles("src/**/*.hpp")
    add_files("src/**/*.cpp")
    add_includedirs("src", {public = true})

    add_packages("imgui");
