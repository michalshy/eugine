cmake_minimum_required(VERSION 3.20)

# Configure project
set(CMAKE_CXX_STANDARD 17)
project(eugine)



# Include directiories
include_directories(${OPENGL_INCLUDE_DIRS}
                    src
                    third_party/include/image
                    third_party/include/KHR
                    third_party/include
                    libs/imgui
                    libs/imgui/backends)

# Include libraries
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)
add_subdirectory(libs/assimp)

include(FetchContent)
FetchContent_Declare(
    glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
    )
    FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)
FetchContent_Declare(imgui_external
	URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.9b.tar.gz
	EXCLUDE_FROM_ALL
)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS)

include_directories( $ENV{BOOST_INCLUDEDIR} )

set(IMGUI_FILES 
    libs/imgui/imgui.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/imgui_tables.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_demo.cpp
    libs/imgui/backends/imgui_impl_opengl3.cpp
    libs/imgui/backends/imgui_impl_glfw.cpp)

# Search for files
file(GLOB_RECURSE SRCs
       ${PROJECT_SOURCE_DIR}/src/*.cpp
       ${PROJECT_SOURCE_DIR}/src/*.hpp
       ${PROJECT_SOURCE_DIR}/src/*.c
       ${PROJECT_SOURCE_DIR}/third_party/*.c
       ${PROJECT_SOURCE_DIR}/third_party/*.cpp)

set(SOURCE_FILES 
    src/main.cpp
    ${SRCs}
    ${IMGUI_FILES})

add_executable(eugine ${SOURCE_FILES})

# commands
add_custom_command(
        TARGET eugine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/config/eugine.cfg
                ${CMAKE_CURRENT_BINARY_DIR}/config/eugine.cfg)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(eugine
	${OPENGL_LIBRARY} 
    glm::glm
    glfw
    assimp
    ${Boost_LIBRARIES}
)
