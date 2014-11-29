cmake_minimum_required(VERSION 2.8.11)

project(amt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(gmock-1.7.0)

enable_testing()

find_package(OpenCV REQUIRED)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gmock-1.7.0/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gmock-1.7.0/gtest/include/)

set(MAIN
	source/main.cpp
)

set(SRC
	source/Area.cpp
	source/CameraFrameSource.cpp
	source/FileFrameSource.cpp
	source/Frame.cpp
	source/Engine.cpp
	source/LockingTimer.cpp
	source/MainWindowWidget.cpp
	source/FrameMovementExtractor.cpp
	source/OpenCVFrameSource.cpp
	source/Timer.cpp
	source/ViewportWidget.cpp
)

set(UI
	ui/mainwindow.ui
)

set(TESTS
	tests/FrameDirReader.cpp
	tests/Samples.cpp
	tests/TestArea.cpp
	tests/TestCameraFrameSource.cpp
	tests/TestFileFrameSource.cpp
	tests/TestFrame.cpp
	tests/TestFrameDirReader.cpp
	tests/TestFrameMovementExtractor.cpp
	tests/main.cpp
)

qt5_wrap_ui(WRAP_UI ${UI})

add_executable(${CMAKE_PROJECT_NAME} ${MAIN} ${SRC} ${WRAP_UI})
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets ${OpenCV_LIBS})

add_executable(${CMAKE_PROJECT_NAME}_ut ${SRC} ${TESTS})
target_link_libraries(${CMAKE_PROJECT_NAME}_ut -lpthread Qt5::Core Qt5::Widgets Qt5::Multimedia ${OpenCV_LIBS} gmock)

add_test(
	NAME ${CMAKE_PROJECT_NAME}_ut
	COMMAND ${CMAKE_PROJECT_NAME}_ut
)

add_custom_command(
	TARGET ${CMAKE_PROJECT_NAME}_ut
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/samples/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/samples/ ${CMAKE_BINARY_DIR}/samples/
	COMMENT "Copying samples"
)
