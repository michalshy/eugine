cmake_minimum_required(VERSION 3.20)

# Configure project
set(CMAKE_CXX_STANDARD 17)
project(eugine)

# Include directiories
include_directories(${OPENGL_INCLUDE_DIRS}
                    include
                    third_party/include/image
                    third_party/include/KHR
                    third_party/include)

# Include libraries
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)

include(FetchContent)
FetchContent_Declare(
    glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
    )
    FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)

# Search for files
file(GLOB_RECURSE SRCs
       ${PROJECT_SOURCE_DIR}/src/*.cpp
       ${PROJECT_SOURCE_DIR}/include/*.hpp
       ${PROJECT_SOURCE_DIR}/src/*.c
       ${PROJECT_SOURCE_DIR}/third_party/*.c
       ${PROJECT_SOURCE_DIR}/third_party/*.cpp)

set(SOURCE_FILES 
    src/main.cpp
    ${SRCs})

add_executable(eugine ${SOURCE_FILES})

target_link_libraries(eugine
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
    glm::glm
    glfw
)
