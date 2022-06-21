cmake_minimum_required(VERSION 3.5)

project(editor_interface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(yaml-cpp)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        create_map.cpp
        create_map.h
        create_map.ui
        edit_map.cpp
        edit_map.h
        edit_map.ui
        map.cpp
        map.h
        yaml_parser.cpp
        yaml_parser.h
        editor.cpp
        editor.h
        editor.ui
        tiles_list.cpp
        tiles_list.h
        map_scene.cpp
        map_scene.h
        map_item.cpp
        map_item.h
        item_info.cpp
        item_info.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(editor_interface
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(editor_interface SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(editor_interface
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(editor_interface PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${YAML_CPP_LIBRARIES})
