cmake_minimum_required(VERSION 3.10.0)
project(SSSS)

# GLFW
option(GLFW_INSTALL OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TEST OFF)
add_subdirectory(external/glfw)

# Add directiores
include_directories(src/
                    external/glfw/include)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
                        glfw
                        ${GLFW_LIBRARIES})