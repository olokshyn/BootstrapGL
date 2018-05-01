cmake_minimum_required(VERSION 3.7)
project(Lightning)

find_package(X11 REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(BootstrapGL)

include_directories(BootstrapGL)
include_directories(BootstrapGL/3rdParty)
include_directories(BootstrapGL/3rdParty/glfw/include)
include_directories(
	BootstrapGL/3rdParty/assimp/include
	${CMAKE_CURRENT_BINARY_DIR}/BootstrapGL/3rdParty/assimp/include)

set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} BootstrapGL)

file(GLOB shaders "${CMAKE_SOURCE_DIR}/shaders/*")
foreach(shader ${shaders})
    get_filename_component(shader_name ${shader} NAME)
    configure_file(${shader} ${CMAKE_BINARY_DIR}/shaders/${shader_name} COPYONLY)
endforeach()

file(GLOB textures "${CMAKE_SOURCE_DIR}/textures/*")
foreach(texture ${textures})
    get_filename_component(texture_name ${texture} NAME)
    configure_file(${texture} ${CMAKE_BINARY_DIR}/textures/${texture_name} COPYONLY)
endforeach()
