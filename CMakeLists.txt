# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project("example" LANGUAGES CXX)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()


add_compile_options(-std=c++11)

# find python libraries
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread system iostreams)
include_directories(
    include 
    ${PYTHON3_INCLUDE_DIRS} 
    ${NumPy_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    )

link_directories(${Boost_LIBRARY_DIRS})
set (LIB_BOOST
    ${LIBRARIES}
    ${Boost_LIBRARIES}
)

# populate matplotlib repository
include(FetchContent)
FetchContent_Declare(
    matplotlib
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG        f23347fca25219d1c42cbb91608b5556814bf572
)
FetchContent_GetProperties(matplotlib)
if(NOT matplotlib_POPULATED)
    FetchContent_Populate(matplotlib)
endif()
include_directories(SYSTEM ${matplotlib_SOURCE_DIR})

# add executable
add_executable(tugas_a src/TugasA/main.cpp)


add_executable(tugas_b src/TugasB/main.cpp)
add_executable(knn src/TugasB/knn.cpp)

add_executable(tugas_c src/TugasC/main.cpp)


add_executable(tugas_d src/TugasD/main.cpp)
add_executable(knn_tugas_d src/TugasD/knn.cpp)

# link python and numpy
target_link_libraries(
        tugas_a ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        Python3::NumPy
)

target_link_libraries(
        tugas_b ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        Python3::NumPy
        ${LIB_BOOST}
)

target_link_libraries(
        knn ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        Python3::NumPy
        ${LIB_BOOST}
)

target_link_libraries(
        tugas_c ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        Python3::NumPy
        ${LIB_BOOST}
)

target_link_libraries(
        tugas_d ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        Python3::NumPy
        ${LIB_BOOST}
)

target_link_libraries(
        knn_tugas_d ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        Python3::NumPy
        ${LIB_BOOST}
)

