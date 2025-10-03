-- Common
add_requires("spdlog", "glm")

-- Graphics
add_requires("glfw", "glad", "stb")
add_requires("imgui v1.92.1-docking", {configs = {glfw_opengl3 = true}})

-- ECS
add_requires("entt", "yaml-cpp")

-- Core Target
target("Core")
    set_kind("static")

    add_headerfiles("Core/**/*.h")    
    add_headerfiles("Core/**/*.hpp")
    add_files("Core/**/*.c")
    add_files("Core/**/*.cpp")
    add_includedirs("Core", {public = true})

    -- Common
    add_packages("spdlog")
    add_packages("glm", {public = true})

    -- Graphics
    add_packages("glfw", "glad", "stb");
    add_packages("imgui", {public = true});

-- Function Target
target("Function")
    set_kind("static")

    add_deps("Core")

    add_headerfiles("Function/**/*.hpp")
    add_files("Function/**/*.cpp")
    add_includedirs("Function", {public = true})

    -- ECS
    add_packages("entt", "yaml-cpp", {public = true})

-- Engine Target
--set_runtimes("MTd")
target("Engine")
    set_kind("static")

    add_deps("Core")
    add_deps("Function")
	
    add_files("*.cpp")