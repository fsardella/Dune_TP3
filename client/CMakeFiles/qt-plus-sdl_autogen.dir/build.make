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
CMAKE_SOURCE_DIR = /home/pilar/Escritorio/tp3_taller/Dune_TP3/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pilar/Escritorio/tp3_taller/Dune_TP3/client

# Utility rule file for qt-plus-sdl_autogen.

# Include the progress variables for this target.
include CMakeFiles/qt-plus-sdl_autogen.dir/progress.make

CMakeFiles/qt-plus-sdl_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/pilar/Escritorio/tp3_taller/Dune_TP3/client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target qt-plus-sdl"
	/usr/bin/cmake -E cmake_autogen /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/CMakeFiles/qt-plus-sdl_autogen.dir/AutogenInfo.json Debug

qt-plus-sdl_autogen: CMakeFiles/qt-plus-sdl_autogen
qt-plus-sdl_autogen: CMakeFiles/qt-plus-sdl_autogen.dir/build.make

.PHONY : qt-plus-sdl_autogen

# Rule to build all files generated by this target.
CMakeFiles/qt-plus-sdl_autogen.dir/build: qt-plus-sdl_autogen

.PHONY : CMakeFiles/qt-plus-sdl_autogen.dir/build

CMakeFiles/qt-plus-sdl_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qt-plus-sdl_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qt-plus-sdl_autogen.dir/clean

CMakeFiles/qt-plus-sdl_autogen.dir/depend:
	cd /home/pilar/Escritorio/tp3_taller/Dune_TP3/client && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pilar/Escritorio/tp3_taller/Dune_TP3/client /home/pilar/Escritorio/tp3_taller/Dune_TP3/client /home/pilar/Escritorio/tp3_taller/Dune_TP3/client /home/pilar/Escritorio/tp3_taller/Dune_TP3/client /home/pilar/Escritorio/tp3_taller/Dune_TP3/client/CMakeFiles/qt-plus-sdl_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qt-plus-sdl_autogen.dir/depend

