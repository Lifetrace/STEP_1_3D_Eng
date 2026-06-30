cmake_minimum_required(VERSION 4.1)

project(LoopEngine LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(LoopEngine src/main.cpp src/Window/WindowInit.cpp src/Other/Debug.cpp)

#target_compile_definitions(LoopEngine PRIVATE LOOP_ENABLE_DEBUG_WINDOWSIZE)

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
