cmake_minimum_required( VERSION 2.8)

project(Droplet_quality_evaluation_count)

# opencv
set(OpenCV_DIR $ENV{OPENCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/include)
include_directories(${OpenCV_DIR}/include/opencv)
include_directories(${OpenCV_DIR}/include/opencv2)

aux_source_directory(. SRCS)
file(GLOB HEAD ./*.h)

add_executable(Droplet_quality_evaluation_count ${SRCS} ${HEAD})

target_link_libraries(Droplet_quality_evaluation_count ${OpenCV_LIBS})
