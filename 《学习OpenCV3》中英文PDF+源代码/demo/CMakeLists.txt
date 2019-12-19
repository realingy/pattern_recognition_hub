cmake_minimum_required( VERSION 2.8)

project(opencv3)

# opencv
set(OpenCV_DIR $ENV{OPENCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/include)
include_directories(${OpenCV_DIR}/include/opencv)
include_directories(${OpenCV_DIR}/include/opencv2)

# aux_source_directory(. SRCS)
# file(GLOB HEAD ./*.h)

add_executable(example_15_01 example_15-01.cpp)
target_link_libraries(example_15_01 ${OpenCV_LIBS})

add_executable(example_15_01_fd example_15_01_帧间差分.cpp)
target_link_libraries(example_15_01_fd ${OpenCV_LIBS})

