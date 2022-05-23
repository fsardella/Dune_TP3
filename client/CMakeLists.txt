cmake_minimum_required(VERSION 3.5)

project(menu1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

if(APPLE)
    message("Estoy en OSX")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2")
endif()

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
add_subdirectory(lib/libSDL2pp)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets)

qt5_wrap_ui(UIS_HEADERS
  mainwindow.ui
)

message("Headers generados: ${UIS_HEADERS}")
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (sdl-standalone
        mainSDL.cpp
        Animation.cpp
        Animation.h
        Gameloop.cpp
        Player.cpp
        Player.h
)

add_executable (qt-standalone
    main.cpp
    mainwindow.cpp
    ${UIS_HEADERS}
)

add_executable (qt-plus-sdl
    mainQtSDL.cpp
    mainwindow.cpp
    Animation.cpp
    Animation.h
    Gameloop.cpp
        Player.cpp
    Player.h
    ${UIS_HEADERS}
)

target_link_libraries(qt-standalone Qt5::Widgets)
target_link_libraries(sdl-standalone ${SDL2PP_LIBRARIES})
target_link_libraries(qt-plus-sdl Qt5::Widgets ${SDL2PP_LIBRARIES})

FILE(COPY assets DESTINATION ${CMAKE_BINARY_DIR})