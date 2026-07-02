cmake_minimum_required(VERSION 3.6)

project(LoopEngine LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(LoopEngine src/main.cpp src/Window/WindowInit.cpp src/Other/Debug.cpp src/Application.cpp)


target_include_directories(LoopEngine PUBLIC ${CMAKE_HOME_DIRECTORY}/include)

#target_link_libraries(LoopEngine PRIVATE ws2_32)

# added glad
add_library(glad STATIC ${CMAKE_HOME_DIRECTORY}/external/glad/src/gl.c)
target_include_directories(glad PUBLIC ${CMAKE_HOME_DIRECTORY}/external/glad/include)
target_link_libraries(LoopEngine PRIVATE glad)

# added glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(LoopEngine PRIVATE glfw)

# added glm
target_include_directories(LoopEngine PRIVATE external/glm)

# DEBUGS
#target_compile_definitions(LoopEngine PRIVATE LOOP_ENABLE_DEBUG_WINDOWSIZE)
#target_compile_definitions(LoopEngine PRIVATE LOOP_ENABLE_CURSOR_DEBUG)
