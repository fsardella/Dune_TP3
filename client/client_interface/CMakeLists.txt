cmake_minimum_required(VERSION 3.5)

project(client_interface VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -DDEBUG -Wall -fno-inline -pedantic -pedantic-errors -pthread")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(yaml-cpp REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        choosehouse.cpp
        choosehouse.h
        choosehouse.ui
        imagehouse.qrc
        maingame.cpp
        maingame.h
        maingame.ui
        creategamewindow.cpp
        creategamewindow.h
        creategamewindow.ui
        joingamewindow.cpp
        joingamewindow.h
        joingamewindow.ui
        ../client_client.cpp
        ../client_client.h
        ../client_protocol.cpp
        ../client_protocol.h
        ../common_socket.cpp
        ../common_socket.h
        ../common_resolver.cpp
        ../common_resolver.h
        ../Area.cpp
        ../Area.h
        ../SdlWindow.cpp
        ../SdlWindow.h
        ../Camera.cpp
        ../Camera.h
        ../Drawer.cpp
        ../Drawer.h
        ../GameView.cpp
        ../GameView.h
        ../MapView.cpp
        ../MapView.h
        ../NonMovable.cpp
        ../NonMovable.h
        ../Renderizable.cpp
        ../Renderizable.h
        ../SdlTexture.cpp
        ../SdlTexture.h
        ../thread.cpp
        ../thread.h
)

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
add_subdirectory(lib/libSDL2pp)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})

message("Headers generados: ${UIS_HEADERS}")
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(client_interface
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${UIS_HEADERS}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET client_interface APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(client_interface SHARED
            ${PROJECT_SOURCES}
            ${UIS_HEADERS}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(client_interface
            ${PROJECT_SOURCES}
            ${UIS_HEADERS}
        )
    endif()
endif()
target_link_libraries(client_interface Qt5::Widgets Qt5::Core ${SDL2PP_LIBRARIES} yaml-cpp)

set_target_properties(client_interface PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(client_interface)
endif()
