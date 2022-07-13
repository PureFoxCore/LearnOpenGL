cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Submodules | add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/L_I_B_N_A_M_E)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# Include submodules | include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/L_I_B_N_A_M_E/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# Link submodules | link_libraries(L_I_B_N_A_M_E)
link_libraries(glfw)
link_libraries(glad)
link_libraries(imgui)

# Project
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/LearnOpenGL)

add_custom_target(copy-compile-commands ALL
     	${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}
	)
