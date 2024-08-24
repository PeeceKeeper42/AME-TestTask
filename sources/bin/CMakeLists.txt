
cmake_minimum_required(VERSION 3.7...3.29)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(TeskTaskMainWindow
        VERSION 1.0.0
        DESCRIPTION "Main window for test task"
        LANGUAGES CXX)

message("Top level CMake project - ${CMAKE_PROJECT_NAME}")
message("Found new CMake project - ${PROJECT_NAME}")

include(${CMAKE_SOURCE_DIR}/../_cmake/paths.cmake)

include(${CMAKE_DIRECTORY}/setup.cmake)
include(${CMAKE_DIRECTORY}/applyConfiguration.cmake)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

set(PROJECT_RESOURCES
    ${RESOURCE_DIRECTORY}/resources_main.qrc
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ImageViewer/imageviewer.h
    ImageViewer/imageviewer.cpp
    ImageViewer/imageviewer.ui
    DataSorter/datasorter.h
    DataSorter/datasorter.cpp
    DataSorter/datasorter.ui
    VideoPlayer/videoPlayer.h
    VideoPlayer/videoPlayer.cpp
    VideoPlayer/videoPlayer.ui
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
    )

target_link_directories(${PROJECT_NAME}
    PRIVATE ${INCLUDE_DIRECTORY}
    PRIVATE ${SYS_LIB_PATH}
)

target_link_libraries(${PROJECT_NAME}
    #PRIVATE _addMeAsLibrary
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
)
















