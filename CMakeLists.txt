cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 23)

# Submodules | add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/L_I_B_N_A_M_E)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)

# Include submodules | include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/L_I_B_N_A_M_E/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)

# Link submodules | link_libraries(L_I_B_N_A_M_E)
link_libraries(glfw)

# Project
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/LearnOpenGL)