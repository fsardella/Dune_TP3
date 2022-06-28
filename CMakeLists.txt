cmake_minimum_required(VERSION 3.5)

project(entrega_parcial LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -DDEBUG -Wall -fno-inline -pedantic -pedantic-errors -pthread")

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

set(EDITOR_SOURCES
        editor/main.cpp
        editor/mainwindow.cpp
        editor/mainwindow.h
        editor/mainwindow.ui
        editor/create_map.cpp
        editor/create_map.h
        editor/create_map.ui
        editor/edit_map.cpp
        editor/edit_map.h
        editor/edit_map.ui
        editor/map.cpp
        editor/map.h
        editor/yaml_parser.cpp
        editor/yaml_parser.h
        editor/editor.cpp
        editor/editor.h
        editor/editor.ui
        editor/tiles_list.cpp
        editor/tiles_list.h
        editor/map_scene.cpp
        editor/map_scene.h
        editor/map_item.cpp
        editor/map_item.h
        editor/item_info.cpp
        editor/item_info.h
)

set(CLIENT_SOURCES
        client/client_interface/main.cpp
        client/client_interface/mainwindow.cpp
        client/client_interface/mainwindow.h
        client/client_interface/mainwindow.ui
        client/client_interface/choosehouse.cpp
        client/client_interface/choosehouse.h
        client/client_interface/choosehouse.ui
        client/client_interface/imagehouse.qrc
        client/client_interface/maingame.cpp
        client/client_interface/maingame.h
        client/client_interface/maingame.ui
        client/client_interface/creategamewindow.cpp
        client/client_interface/creategamewindow.h
        client/client_interface/creategamewindow.ui
        client/client_interface/joingamewindow.cpp
        client/client_interface/joingamewindow.h
        client/client_interface/joingamewindow.ui
        client/client_interface/waitingWindow.cpp
        client/client_interface/waitingWindow.h
        client/client_interface/waitingWindow.ui
        client/client_interface/losewindow.cpp
        client/client_interface/losewindow.h
        client/client_interface/losewindow.ui
        client/client_interface/winwindow.cpp
        client/client_interface/winwindow.h
        client/client_interface/winwindow.ui
        client/BlockingQueue.h
        client/client_client.cpp
        client/client_client.h
        client/client_protocol.cpp
        client/client_protocol.h
        client/common_socket.cpp
        client/common_socket.h
        client/common_resolver.cpp
        client/common_resolver.h
        client/Area.cpp
        client/Area.h
        client/SdlWindow.cpp
        client/SdlWindow.h
        client/Camera.cpp
        client/Camera.h
        client/Drawer.cpp
        client/Drawer.h
        client/GameView.cpp
        client/GameView.h
        client/MapView.cpp
        client/MapView.h
        client/Renderizable.cpp
        client/Renderizable.h
        client/SdlTexture.cpp
        client/SdlTexture.h
        client/ServerReceiver.cpp
        client/ServerReceiver.h
        client/Construction.cpp
        client/Construction.h
        client/thread.cpp
        client/thread.h
        client/BackGroundTile.cpp
        client/BackGroundTile.h
        client/UserInputReceiver.cpp
        client/UserInputReceiver.h
        client/ServerDespatcher.cpp
        client/ServerDespatcher.h
        client/ClientInput.cpp
        client/ClientInput.h
        client/Unit.cpp
        client/Unit.h
        client/MenuImage.cpp
        client/MenuImage.h
        client/MenuText.cpp
        client/MenuText.h
        client/Animation.cpp
        client/Animation.h
        client/GameWaiter.cpp
        client/GameWaiter.h
)

set(SERVER_SOURCES
        server/common_blockingqueue.h
        server/common_resolver.cpp
        server/common_resolver.h
        server/common_socket.cpp
        server/common_socket.h
        server/common_thread.cpp
        server/common_thread.h
        server/server_activegame.cpp
        server/server_activegame.h
        server/server_astar.cpp
        server/server_astar.h
        server/server_broadcaster.cpp
        server/server_broadcaster.h
        server/server_command.cpp
        server/server_command.h
        server/server_game.cpp
        server/server_game.h
        server/server_gamedata.cpp
        server/server_gamedata.h
        server/server_gamehandler.cpp
        server/server_gamehandler.h
        server/server_gameSet.cpp
        server/server_gameSet.h
        server/server_inputguy.cpp
        server/server_inputguy.h
        server/server_listener.cpp
        server/server_listener.h
        server/server_player.cpp
        server/server_player.h
        server/server_protocol.cpp
        server/server_protocol.h
        server/server_sender.cpp
        server/server_sender.h
        server/server_server.cpp
        server/server_server.h
        server/server_talker.cpp
        server/server_talker.h
        server/server_terrain_map.cpp
        server/server_terrain_map.h
        server/server_terrains.cpp
        server/server_terrains.h
        server/server_timewizard.cpp
        server/server_timewizard.h
        server/server_unitdata.cpp
        server/server_unitdata.h
        server/server_units.cpp
        server/server_units.h
)

SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
add_subdirectory(client/client_interface/lib/libSDL2pp)
include_directories(${SDL2PP_INCLUDE_DIRS})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(editor_interface
        ${EDITOR_SOURCES}
    )
    qt_add_executable(client_interface
        ${CLIENT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(editor_interface SHARED
            ${EDITOR_SOURCES}
        )
        add_library(client_interface SHARED
            ${CLIENT_SOURCES}
        )
        add_library(server SHARED
            ${SERVER_SOURCES}
        )
    else()
        add_executable(editor_interface
            ${EDITOR_SOURCES}
        )
        add_executable(client_interface
            ${CLIENT_SOURCES}
        )
        # add_executable(server
        #     ${SERVER_SOURCES}
        # )
    endif()
endif()

add_executable(server ${SERVER_SOURCES} server/main.cpp)

target_link_libraries(editor_interface PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${YAML_CPP_LIBRARIES})
target_link_libraries(client_interface Qt5::Widgets Qt5::Core ${SDL2PP_LIBRARIES} yaml-cpp)
target_link_libraries(server ${YAML_CPP_LIBRARIES})
