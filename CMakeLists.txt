cmake_minimum_required(VERSION 3.14)

project(JellyPlayer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

set(PROJECT_SOURCES
    windowmanager.h
    windowmanager.cpp
    main.cpp
    qml.qrc
)

add_executable(JellyPlayer ${PROJECT_SOURCES})
target_link_libraries(JellyPlayer PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets)

target_include_directories(JellyPlayer PRIVATE "${JellyPlayer_SOURCE_DIR}/libvlcpp")

IF(WIN32)
    set(VLCWINX64_DIR "$ENV{USERPROFILE}/.nuget/packages/videolan.libvlc.windows/3.0.12/build/x64/")
    target_include_directories(JellyPlayer PRIVATE ${VLCWINX64_DIR}/include)
    target_link_libraries(JellyPlayer PRIVATE ${VLCWINX64_DIR}/libvlc.dll ${VLCWINX64_DIR}/libvlccore.dll)
ELSE()
    target_link_libraries(JellyPlayer PRIVATE vlc)
ENDIF()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/video.mp4
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
