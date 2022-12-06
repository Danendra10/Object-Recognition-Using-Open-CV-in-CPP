cmake_minimum_required(VERSION 3.0)
project(histogram_learning)

include_directories(
    include
)

find_package(OpenCV REQUIRED)

add_executable(tugas_a src/TugasA/main.cpp)
target_link_libraries(tugas_a ${OpenCV_LIBS})