cmake_minimum_required(VERSION 3.10)
project(RNN_SLAM LANGUAGES CXX)

# ==============================
# C++ Standard
# ==============================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ==============================
# Dependencies
# ==============================
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
find_package(OpenMP)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Pangolin REQUIRED)

# ==============================
# Third-party
# ==============================
add_subdirectory(thirdparty/Sophus)

# ==============================
# DSO Core sources
# ==============================
file(GLOB_RECURSE DSO_SOURCES src/*.cpp)

list(REMOVE_ITEM DSO_SOURCES
    ${PROJECT_SOURCE_DIR}/src/main_dso_pangolin.cpp
	${PROJECT_SOURCE_DIR}/src/IOWrapper/ImageRW_dummy.cpp
)

# ==============================
# DSO Core library
# ==============================
add_library(dso_core STATIC ${DSO_SOURCES})

target_include_directories(dso_core PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/thirdparty/Sophus
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${Pangolin_INCLUDE_DIRS}
)

target_link_libraries(dso_core PUBLIC
    Eigen3::Eigen
    ${OpenCV_LIBS}
    Boost::system
    Boost::thread
    Boost::filesystem
    Python3::Python
    ${GLEW_LIBRARIES}
    OpenGL::GL
    ${Pangolin_LIBRARIES}
)

# ==============================
# Executable
# ==============================
add_executable(rnn_slam_vm
    src/main_dso_pangolin.cpp
)

target_compile_options(rnn_slam_vm PRIVATE
    -O3
    -march=native
    -Wall
)

target_compile_definitions(rnn_slam_vm PRIVATE
    BOOST_BIND_GLOBAL_PLACEHOLDERS
)

target_link_libraries(rnn_slam_vm PRIVATE
    dso_core
)

if(OpenMP_CXX_FOUND)
    target_link_libraries(rnn_slam_vm PRIVATE OpenMP::OpenMP_CXX)
endif()