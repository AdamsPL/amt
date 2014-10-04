cmake_minimum_required(VERSION 2.8.11)

project(amt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing()

find_package(OpenCV REQUIRED)

find_package(GTest REQUIRED)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5MultimediaWidgets REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)

set(MAIN
	source/main.cpp
)

set(SRC
	source/FrameSource.cpp
	source/CameraFrameSource.cpp
	source/FileFrameSource.cpp
)

set(UI
	ui/mainwindow.ui
)

set(TESTS
	tests/Samples.cpp
	tests/FrameDirReader.cpp
	tests/TestFrameDirReader.cpp
	tests/TestFrameSource.cpp
	tests/TestFileFrameSource.cpp
)

qt5_wrap_ui(WRAP_UI ${UI})

add_executable(${CMAKE_PROJECT_NAME} ${MAIN} ${SRC} ${WRAP_UI})
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets ${OpenCV_LIBS})

add_executable(${CMAKE_PROJECT_NAME}_ut ${SRC} ${TESTS})
target_link_libraries(${CMAKE_PROJECT_NAME}_ut ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARY} -lpthread -lgmock Qt5::Core Qt5::Widgets Qt5::Multimedia)

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
