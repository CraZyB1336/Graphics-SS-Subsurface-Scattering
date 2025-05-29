cmake_minimum_required(VERSION 3.10.0)
project(SSSS)

# GLFW
option(GLFW_INSTALL OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TEST OFF)
add_subdirectory(external/glfw)

# ASSIMP
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
add_subdirectory(external/assimp)

# Add directiores
include_directories(src/
                    external/glad/include
                    external/glfw/include
                    external/glm/
                    external/assimp/include
                    external/)

# Add files
file (GLOB          VENDORS_SOURCES     external/glad/src/glad.c
                                        external/stb_image/stb_image_impl.cpp)
file (GLOB_RECURSE  PROJECT_HEADERS     src/*.hpp
                                        src/*.h)
file (GLOB_RECURSE  PROJECT_SOURCES     src/*.cpp
                                        src/*.c)
#file (GLOB_RECURSE  PROJECT_SHADERS     src)

add_executable(${PROJECT_NAME}  ${PROJECT_SOURCES}
                                ${PROJECT_HEADERS}
                                ${VENDORS_SOURCES})

target_link_libraries(${PROJECT_NAME}
                        glfw
                        assimp
                        ${GLFW_LIBRARIES}
                        ${GLAD_LIBRARIES})