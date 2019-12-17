cmake_minimum_required( VERSION 2.8)

project(Droplet_quality_evaluation_count)

# Qt库查询
set(Qt5_DIR $ENV{QT590}/lib/cmake/Qt5)
message(${Qt5_DIR})
set(ACTIVE_QT_DIR $ENV{QT590})

# Qt查询路径
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${ACTIVE_QT_DIR}")
# set(INSTALL_PREFIX_INITIALIZED ${CMAKE_CURRENT_SOURCE_DIR}/build/install CACHE STRINGS "change prefix")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)
# set(RESOURCE_DIR resources/resources.qrc)
# find_package(Qt5 REQUIRED Widgets Core QtGui)
find_package(Qt5 REQUIRED Widgets)
# qt5_wrap_cpp( MOC widget.h)
# qt5_wrap_ui( UIC widget.ui)
# qt5_add_resources(RCC resources.qrc)
# 自动moc, uic 和 rcc

# file(GLOB ui_files *.ui)
# file(GLOB resource_files *.qrc)
# 在配置lib或exe时需要将resource 文件和 ui 文件添加进去
# add_executable(${app_name} ${headers} ${ui_files} ${resource_files})
# find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
# target_link_libraries(${app_name} Qt5::Core Qt5::Gui Qt5::Widgets)

# opencv
set(OpenCV_DIR $ENV{OPENCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/include)
include_directories(${OpenCV_DIR}/include/opencv)
include_directories(${OpenCV_DIR}/include/opencv2)

aux_source_directory(. SRCS)
file(GLOB HEAD ./*.h)

add_executable(Droplet_quality_evaluation_count ${SRCS} ${HEAD})

target_link_libraries(Droplet_quality_evaluation_count ${OpenCV_LIBS} Qt5::Widgets)
