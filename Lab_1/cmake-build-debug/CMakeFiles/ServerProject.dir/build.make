# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\CLion\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\CLion\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\Learning\network-application-programming\Lab_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\Learning\network-application-programming\Lab_1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ServerProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ServerProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ServerProject.dir/flags.make

CMakeFiles/ServerProject.dir/main.cpp.obj: CMakeFiles/ServerProject.dir/flags.make
CMakeFiles/ServerProject.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Learning\network-application-programming\Lab_1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ServerProject.dir/main.cpp.obj"
	"E:\MinGW(C++ Compilier)\mingw32\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\ServerProject.dir\main.cpp.obj -c F:\Learning\network-application-programming\Lab_1\main.cpp

CMakeFiles/ServerProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerProject.dir/main.cpp.i"
	"E:\MinGW(C++ Compilier)\mingw32\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\Learning\network-application-programming\Lab_1\main.cpp > CMakeFiles\ServerProject.dir\main.cpp.i

CMakeFiles/ServerProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerProject.dir/main.cpp.s"
	"E:\MinGW(C++ Compilier)\mingw32\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\Learning\network-application-programming\Lab_1\main.cpp -o CMakeFiles\ServerProject.dir\main.cpp.s

# Object files for target ServerProject
ServerProject_OBJECTS = \
"CMakeFiles/ServerProject.dir/main.cpp.obj"

# External object files for target ServerProject
ServerProject_EXTERNAL_OBJECTS =

ServerProject.exe: CMakeFiles/ServerProject.dir/main.cpp.obj
ServerProject.exe: CMakeFiles/ServerProject.dir/build.make
ServerProject.exe: CMakeFiles/ServerProject.dir/linklibs.rsp
ServerProject.exe: CMakeFiles/ServerProject.dir/objects1.rsp
ServerProject.exe: CMakeFiles/ServerProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\Learning\network-application-programming\Lab_1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ServerProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ServerProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ServerProject.dir/build: ServerProject.exe

.PHONY : CMakeFiles/ServerProject.dir/build

CMakeFiles/ServerProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ServerProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ServerProject.dir/clean

CMakeFiles/ServerProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\Learning\network-application-programming\Lab_1 F:\Learning\network-application-programming\Lab_1 F:\Learning\network-application-programming\Lab_1\cmake-build-debug F:\Learning\network-application-programming\Lab_1\cmake-build-debug F:\Learning\network-application-programming\Lab_1\cmake-build-debug\CMakeFiles\ServerProject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ServerProject.dir/depend

