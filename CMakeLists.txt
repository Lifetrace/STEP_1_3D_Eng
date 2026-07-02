cmake_minimum_required(VERSION 3.6)

project(LoopEngine LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(LoopEngine src/main.cpp
src/Window/WindowInit.cpp
src/Other/Debug.cpp
src/Graphics/ShaderInit.cpp
src/Application.cpp
src/Graphics/Buffers.cpp
src/loaders/PngLoader.cpp
src/Graphics/Texture.cpp
)


find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

target_link_libraries(LoopEngine PRIVATE
    ZLIB::ZLIB
    PNG::PNG
)


file(GLOB_RECURSE ASSET_FILES
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/assets/*"
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:LoopEngine>/assets"
    DEPENDS ${ASSET_FILES}
    COMMENT "Copying assets to executable directory"
)

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
