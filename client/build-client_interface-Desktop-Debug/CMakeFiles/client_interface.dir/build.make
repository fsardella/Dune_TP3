# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/client_interface.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client_interface.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client_interface.dir/flags.make

client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/imagehouse.qrc
client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp: CMakeFiles/client_interface_autogen.dir/AutoRcc_imagehouse_EWIEGA46WW_Info.json
client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/d2katreides.png
client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/d2kharkonnen.png
client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/images/d2kordos.png
client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp: /usr/lib/qt5/bin/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for imagehouse.qrc"
	/usr/bin/cmake -E cmake_autorcc /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles/client_interface_autogen.dir/AutoRcc_imagehouse_EWIEGA46WW_Info.json Debug

CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.o: client_interface_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/client_interface_autogen/mocs_compilation.cpp

CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/client_interface_autogen/mocs_compilation.cpp > CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.i

CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/client_interface_autogen/mocs_compilation.cpp -o CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.s

CMakeFiles/client_interface.dir/main.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/main.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client_interface.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/main.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/main.cpp

CMakeFiles/client_interface.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/main.cpp > CMakeFiles/client_interface.dir/main.cpp.i

CMakeFiles/client_interface.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/main.cpp -o CMakeFiles/client_interface.dir/main.cpp.s

CMakeFiles/client_interface.dir/mainwindow.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/mainwindow.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/client_interface.dir/mainwindow.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/mainwindow.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/mainwindow.cpp

CMakeFiles/client_interface.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/mainwindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/mainwindow.cpp > CMakeFiles/client_interface.dir/mainwindow.cpp.i

CMakeFiles/client_interface.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/mainwindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/mainwindow.cpp -o CMakeFiles/client_interface.dir/mainwindow.cpp.s

CMakeFiles/client_interface.dir/choosehouse.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/choosehouse.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/choosehouse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/client_interface.dir/choosehouse.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/choosehouse.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/choosehouse.cpp

CMakeFiles/client_interface.dir/choosehouse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/choosehouse.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/choosehouse.cpp > CMakeFiles/client_interface.dir/choosehouse.cpp.i

CMakeFiles/client_interface.dir/choosehouse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/choosehouse.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/choosehouse.cpp -o CMakeFiles/client_interface.dir/choosehouse.cpp.s

CMakeFiles/client_interface.dir/maingame.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/maingame.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/maingame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/client_interface.dir/maingame.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/maingame.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/maingame.cpp

CMakeFiles/client_interface.dir/maingame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/maingame.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/maingame.cpp > CMakeFiles/client_interface.dir/maingame.cpp.i

CMakeFiles/client_interface.dir/maingame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/maingame.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/maingame.cpp -o CMakeFiles/client_interface.dir/maingame.cpp.s

CMakeFiles/client_interface.dir/creategamewindow.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/creategamewindow.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/creategamewindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/client_interface.dir/creategamewindow.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/creategamewindow.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/creategamewindow.cpp

CMakeFiles/client_interface.dir/creategamewindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/creategamewindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/creategamewindow.cpp > CMakeFiles/client_interface.dir/creategamewindow.cpp.i

CMakeFiles/client_interface.dir/creategamewindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/creategamewindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/creategamewindow.cpp -o CMakeFiles/client_interface.dir/creategamewindow.cpp.s

CMakeFiles/client_interface.dir/joingamewindow.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/joingamewindow.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/joingamewindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/client_interface.dir/joingamewindow.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/joingamewindow.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/joingamewindow.cpp

CMakeFiles/client_interface.dir/joingamewindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/joingamewindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/joingamewindow.cpp > CMakeFiles/client_interface.dir/joingamewindow.cpp.i

CMakeFiles/client_interface.dir/joingamewindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/joingamewindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface/joingamewindow.cpp -o CMakeFiles/client_interface.dir/joingamewindow.cpp.s

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp > CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.i

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp -o CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.s

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp > CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.i

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp -o CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.s

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp > CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.i

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp -o CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.s

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.o: /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp > CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.i

CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp -o CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.s

CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.o: CMakeFiles/client_interface.dir/flags.make
CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.o: client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.o -c /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp

CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp > CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.i

CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp -o CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.s

# Object files for target client_interface
client_interface_OBJECTS = \
"CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/client_interface.dir/main.cpp.o" \
"CMakeFiles/client_interface.dir/mainwindow.cpp.o" \
"CMakeFiles/client_interface.dir/choosehouse.cpp.o" \
"CMakeFiles/client_interface.dir/maingame.cpp.o" \
"CMakeFiles/client_interface.dir/creategamewindow.cpp.o" \
"CMakeFiles/client_interface.dir/joingamewindow.cpp.o" \
"CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.o" \
"CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.o" \
"CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.o" \
"CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.o" \
"CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.o"

# External object files for target client_interface
client_interface_EXTERNAL_OBJECTS =

client_interface: CMakeFiles/client_interface.dir/client_interface_autogen/mocs_compilation.cpp.o
client_interface: CMakeFiles/client_interface.dir/main.cpp.o
client_interface: CMakeFiles/client_interface.dir/mainwindow.cpp.o
client_interface: CMakeFiles/client_interface.dir/choosehouse.cpp.o
client_interface: CMakeFiles/client_interface.dir/maingame.cpp.o
client_interface: CMakeFiles/client_interface.dir/creategamewindow.cpp.o
client_interface: CMakeFiles/client_interface.dir/joingamewindow.cpp.o
client_interface: CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_client.cpp.o
client_interface: CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_protocol.cpp.o
client_interface: CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_socket.cpp.o
client_interface: CMakeFiles/client_interface.dir/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/common_resolver.cpp.o
client_interface: CMakeFiles/client_interface.dir/client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp.o
client_interface: CMakeFiles/client_interface.dir/build.make
client_interface: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.12.8
client_interface: /usr/lib/x86_64-linux-gnu/libSDL2main.a
client_interface: lib/libSDL2pp/libSDL2pp.a
client_interface: /usr/lib/x86_64-linux-gnu/libSDL2.so
client_interface: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
client_interface: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
client_interface: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.12.8
client_interface: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
client_interface: CMakeFiles/client_interface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable client_interface"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_interface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client_interface.dir/build: client_interface

.PHONY : CMakeFiles/client_interface.dir/build

CMakeFiles/client_interface.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_interface.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_interface.dir/clean

CMakeFiles/client_interface.dir/depend: client_interface_autogen/EWIEGA46WW/qrc_imagehouse.cpp
	cd /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/client_interface /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/build-client_interface-Desktop-Debug/CMakeFiles/client_interface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client_interface.dir/depend

