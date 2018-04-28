cmake_minimum_required(VERSION 3.7)
project(BootstrapGL)

find_package(X11 REQUIRED)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(3rdParty/glfw)

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(3rdParty/assimp)

include_directories(3rdParty)
include_directories(3rdParty/glfw/include)
include_directories(
        3rdParty/assimp/include
        ${CMAKE_CURRENT_BINARY_DIR}/3rdParty/assimp/include)

file(GLOB SOURCE_FILES
        */*.cpp
        */*.hpp)

add_library(${PROJECT_NAME}
        ${SOURCE_FILES}
        3rdParty/glad/glad.c)

target_link_libraries(${PROJECT_NAME}
        glfw
        assimp
	m
        ${CMAKE_DL_LIBS}
        ${X11_LIBRARIES}
        Xrandr
        Xxf86vm
        Xinerama
        Xcursor
        pthread)
