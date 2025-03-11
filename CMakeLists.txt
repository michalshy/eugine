cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
project(idk_eng)

include(FetchContent)
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)
FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)

add_subdirectory(libs/glfw)

include_directories(${OPENGL_INCLUDE_DIRS}
                    include/image
                    include/glad
                    include/KHR
                    include)

set(SOURCE_FILES 
    main.cpp
    third_party/glad.c
    third_party/image.cpp)

add_executable(idk_eng ${SOURCE_FILES})

target_link_libraries(idk_eng
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
	${GLFW_LIBRARY}
    glm::glm
    glfw
)
