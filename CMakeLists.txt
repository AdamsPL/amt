cmake_minimum_required(VERSION 2.8.11)

project(amt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_BUILD_TYPE Release)

enable_testing()

find_package(OpenCV REQUIRED)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)

find_file(DUPA NAMES test PATH /tmp/)

add_library(libgmock.a STATIC IMPORTED)
add_library(libgtest.a STATIC IMPORTED)

message(${DUPA})

set(MAIN
	source/main.cpp
)

set(SRC
	source/MainWindowWidget.cpp
	source/MovementDetector.cpp
	source/FrameListener.cpp
	source/FrameStreamer.cpp
	source/CameraFrameSource.cpp
	source/FileFrameSource.cpp
	source/Frame.cpp
	source/OpenCVFrameSource.cpp
	source/ViewportWidget.cpp
	source/Timer.cpp
	source/LockingTimer.cpp
)

set(UI
	ui/mainwindow.ui
)

set(TESTS
	tests/main.cpp
	tests/FrameDirReader.cpp
	tests/Samples.cpp
	tests/TestCameraFrameSource.cpp
	tests/TestFileFrameSource.cpp
	tests/TestFrame.cpp
	tests/TestFrameDirReader.cpp
	tests/TestFrameStreamer.cpp
	tests/TestMovementDetector.cpp
)

qt5_wrap_ui(WRAP_UI ${UI})

add_executable(${CMAKE_PROJECT_NAME} ${MAIN} ${SRC} ${WRAP_UI})
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets ${OpenCV_LIBS})

add_executable(${CMAKE_PROJECT_NAME}_ut ${SRC} ${TESTS})
target_link_libraries(${CMAKE_PROJECT_NAME}_ut -lpthread Qt5::Core Qt5::Widgets Qt5::Multimedia ${OpenCV_LIBS} -lgtest -lgmock)

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
