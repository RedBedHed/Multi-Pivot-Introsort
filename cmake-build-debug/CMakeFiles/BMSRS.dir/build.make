# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\evcmo\CLionProjects\BMSRS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\evcmo\CLionProjects\BMSRS\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BMSRS.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/BMSRS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BMSRS.dir/flags.make

CMakeFiles/BMSRS.dir/main.cpp.obj: CMakeFiles/BMSRS.dir/flags.make
CMakeFiles/BMSRS.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\evcmo\CLionProjects\BMSRS\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BMSRS.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\BMSRS.dir\main.cpp.obj -c C:\Users\evcmo\CLionProjects\BMSRS\main.cpp

CMakeFiles/BMSRS.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BMSRS.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\evcmo\CLionProjects\BMSRS\main.cpp > CMakeFiles\BMSRS.dir\main.cpp.i

CMakeFiles/BMSRS.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BMSRS.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\evcmo\CLionProjects\BMSRS\main.cpp -o CMakeFiles\BMSRS.dir\main.cpp.s

CMakeFiles/BMSRS.dir/sort.cpp.obj: CMakeFiles/BMSRS.dir/flags.make
CMakeFiles/BMSRS.dir/sort.cpp.obj: ../sort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\evcmo\CLionProjects\BMSRS\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BMSRS.dir/sort.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\BMSRS.dir\sort.cpp.obj -c C:\Users\evcmo\CLionProjects\BMSRS\sort.cpp

CMakeFiles/BMSRS.dir/sort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BMSRS.dir/sort.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\evcmo\CLionProjects\BMSRS\sort.cpp > CMakeFiles\BMSRS.dir\sort.cpp.i

CMakeFiles/BMSRS.dir/sort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BMSRS.dir/sort.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\evcmo\CLionProjects\BMSRS\sort.cpp -o CMakeFiles\BMSRS.dir\sort.cpp.s

CMakeFiles/BMSRS.dir/extra.cpp.obj: CMakeFiles/BMSRS.dir/flags.make
CMakeFiles/BMSRS.dir/extra.cpp.obj: ../extra.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\evcmo\CLionProjects\BMSRS\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BMSRS.dir/extra.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\BMSRS.dir\extra.cpp.obj -c C:\Users\evcmo\CLionProjects\BMSRS\extra.cpp

CMakeFiles/BMSRS.dir/extra.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BMSRS.dir/extra.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\evcmo\CLionProjects\BMSRS\extra.cpp > CMakeFiles\BMSRS.dir\extra.cpp.i

CMakeFiles/BMSRS.dir/extra.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BMSRS.dir/extra.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\evcmo\CLionProjects\BMSRS\extra.cpp -o CMakeFiles\BMSRS.dir\extra.cpp.s

# Object files for target BMSRS
BMSRS_OBJECTS = \
"CMakeFiles/BMSRS.dir/main.cpp.obj" \
"CMakeFiles/BMSRS.dir/sort.cpp.obj" \
"CMakeFiles/BMSRS.dir/extra.cpp.obj"

# External object files for target BMSRS
BMSRS_EXTERNAL_OBJECTS =

BMSRS.exe: CMakeFiles/BMSRS.dir/main.cpp.obj
BMSRS.exe: CMakeFiles/BMSRS.dir/sort.cpp.obj
BMSRS.exe: CMakeFiles/BMSRS.dir/extra.cpp.obj
BMSRS.exe: CMakeFiles/BMSRS.dir/build.make
BMSRS.exe: CMakeFiles/BMSRS.dir/linklibs.rsp
BMSRS.exe: CMakeFiles/BMSRS.dir/objects1.rsp
BMSRS.exe: CMakeFiles/BMSRS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\evcmo\CLionProjects\BMSRS\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable BMSRS.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\BMSRS.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BMSRS.dir/build: BMSRS.exe
.PHONY : CMakeFiles/BMSRS.dir/build

CMakeFiles/BMSRS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\BMSRS.dir\cmake_clean.cmake
.PHONY : CMakeFiles/BMSRS.dir/clean

CMakeFiles/BMSRS.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\evcmo\CLionProjects\BMSRS C:\Users\evcmo\CLionProjects\BMSRS C:\Users\evcmo\CLionProjects\BMSRS\cmake-build-debug C:\Users\evcmo\CLionProjects\BMSRS\cmake-build-debug C:\Users\evcmo\CLionProjects\BMSRS\cmake-build-debug\CMakeFiles\BMSRS.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BMSRS.dir/depend

