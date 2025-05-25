cmake_minimum_required(VERSION 3.10.0)
project(SSSS)

# GLFW
option(GLFW_INSTALL OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TEST OFF)
add_subdirectory(external/glfw)

# ASSIMP
option(ASSIMP_INSTALL OFF)
add_subdirectory(external/assimp)

# Add directiores
include_directories(src/
                    external/glad/include
                    external/glfw/include
                    external/glm/
                    external/assimp/include)

# Add files
file (GLOB          VENDORS_SOURCES     external/glad/src/glad.c)
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
                        ${GLFW_LIBRARIES}
                        ${GLAD_LIBRARIES})