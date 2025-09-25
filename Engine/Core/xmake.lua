-- Common
add_requires("spdlog", "glm")

-- Graphics
add_requires("glfw", "glad")
add_requires("imgui v1.92.1-docking", {configs = {glfw_opengl3 = true}})

target("Core")
    set_kind("static")
    
    add_headerfiles("src/**/*.hpp")
    add_files("src/**/*.cpp")
    add_includedirs("src", {public = true})

    -- Common
    add_packages("spdlog")
    add_packages("glm", {public = true})

    -- Graphics
    add_packages("glfw", "glad")
    add_packages("imgui");
